#!/usr/bin/env python3

import psutil


def killAllTelnet():
    for proc in psutil.process_iter(["pid", "name"]):
        if proc.info["name"] == "telnet":
            proc.terminate()


def main():
    killAllTelnet()


if __name__ == "__main__":
    main()
