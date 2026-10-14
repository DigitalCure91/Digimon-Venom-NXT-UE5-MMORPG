#!/usr/bin/env python3
"""Run native pure-core and real-source adapter tests without Unreal Engine."""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import time


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--jobs", type=int, default=4, help="Parallel test processes (default: 4).")
    parser.add_argument("--output", type=Path, help="Log/report directory; default: plugin Intermediate/PortableTests.")
    args = parser.parse_args()
    root = Path(__file__).resolve().parent.parent
    output = (args.output or root / "Intermediate" / "PortableTests").resolve()
    if not shutil.which("g++"):
        parser.error("g++ with C++17 support must be on PATH for the native cores and adapters.")
    output.mkdir(parents=True, exist_ok=True)
    suites = sorted((root / "Tools").glob("test_*.cpp")) + sorted((root / "Tools").glob("test_*.py"))

    def run(suite: Path) -> dict:
        started = time.monotonic()
        log = ""
        code = 1
        try:
            with tempfile.TemporaryDirectory(prefix="digimon-portable-") as temporary:
                commands = [[sys.executable, str(suite)]]
                if suite.suffix == ".cpp":
                    executable = str(Path(temporary) / ("test.exe" if sys.platform == "win32" else "test"))
                    commands = [["g++", "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
                                 "-I" + str(root / "Source" / "DigimonVenomNXTRuntime" / "Public"),
                                 str(suite), "-o", executable], [executable]]
                for command in commands:
                    result = subprocess.run(command, cwd=root, capture_output=True, text=True, timeout=180)
                    log += result.stdout + result.stderr
                    code = result.returncode
                    if code:
                        break
        except (OSError, subprocess.TimeoutExpired) as error:
            log += str(error)
            code = 124 if isinstance(error, subprocess.TimeoutExpired) else 1
        log_path = output / (suite.name + ".log")
        log_path.write_text(log, encoding="utf-8")
        return {"name": suite.name, "exitCode": code, "seconds": round(time.monotonic() - started, 2),
                "log": log_path.name}

    results = []
    with ThreadPoolExecutor(max_workers=max(1, min(args.jobs, 16))) as executor:
        for future in as_completed([executor.submit(run, suite) for suite in suites]):
            result = future.result()
            results.append(result)
            print(("PASS " if result["exitCode"] == 0 else "FAIL ") + result["name"], flush=True)
    failures = [result for result in results if result["exitCode"]]
    report = {"schemaVersion": 1, "total": len(results), "passed": len(results) - len(failures),
              "failed": len(failures), "unrealBuildExecuted": False,
              "suites": sorted(results, key=lambda result: result["name"])}
    report_path = output / "results.json"
    report_path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"{report['passed']}/{report['total']} portable suites passed. Report: {report_path}")
    if failures:
        for failure in failures:
            print(f"Read {output / failure['log']}", file=sys.stderr)
    print("Unreal compilation, import, cook, launch and multiplayer play testing are separate checks.")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
