#!/usr/bin/env python3


import os
import sys
import telnetlib
import subprocess as sb
import time
from termcolor import colored

INPUT_DIR = "tests/input/"
OUTPUT_DIR = "tests/output/"

HOST = "localhost"
PORT = "4242"
TIMEOUT = 1

SUCCESS_ICON = "✓"
FAILURE_ICON = "✗"


def getInputOutput(filename: str):
    with open(INPUT_DIR + filename) as input_file:
        with open(OUTPUT_DIR + filename) as output_file:
            tmp_i = [x[:-1] if x[-1] == "\n" else x for x in input_file.readlines()]
            tmp_o = [x[:-1] if x[-1] == "\n" else x for x in output_file.readlines()]
            input = []
            output = []
            imports = 0
            for i in range(len(tmp_i)):
                if tmp_i[i].startswith("import "):
                    prefix_input, prefix_output = getInputOutput(tmp_i[i][7:])
                    input += prefix_input
                    output += prefix_output
                    imports += 1
                else:
                    input.append(tmp_i[i].encode())
                    try:
                        output.append(tmp_o[i - imports].encode())
                    except:
                        print(f"Invalid Test File:{filename}")
                        exit(1)
            return input, output


def b2s(b: bytes):
    return str(b)[2:-1]


def formatResult(input: bytes, expected: bytes, got: bytes):
    res: str = colored(f" > ", on_color="on_blue")
    res += colored(f" {b2s(input)}\n", "blue")
    res += colored(f" + ", on_color="on_green")
    res += colored(f" {b2s(expected)[:-2]}\n", "green")
    res += colored(f" - ", on_color="on_red")
    res += colored(f" {b2s(got)[:-2]}\n", "red")

    return res


def isCommand(bs: bytes):
    return bs.startswith(". ".encode())


def executeCommand(cmd: bytes):
    sb.run(str(cmd), shell=True)


def test(testName: str, input: list[bytes], output: list[bytes]):
    CONNECTION_SUCCESS = "000 Service ready.\n".encode()
    # print(input)
    # print(output)
    try:
        if len(input) != len(output):
            for i in range(len(input)):
                try:
                    print(f"{input[i]} => {output[i]}")
                except:
                    pass
            raise ValueError(colored(f'Invalid Test File: "{testName}"', "magenta"))

        client = telnetlib.Telnet(HOST, PORT)
        got = client.read_until(CONNECTION_SUCCESS, TIMEOUT)

        if got != CONNECTION_SUCCESS:
            client.close()
            raise ValueError(
                formatResult(
                    "Connection Received (Client Birth)".encode(),
                    CONNECTION_SUCCESS,
                    got,
                )
            )

        for i in range(len(input)):
            if isCommand(input[i]):
                executeCommand(input[i])  # should wait the end of the command
                continue
            expected = output[i] + "\n".encode()
            client.write(input[i] + "\n".encode())
            got = client.read_until(expected, TIMEOUT)
            if expected != got:
                client.close()
                raise ValueError(formatResult(input[i], expected, got))

        client.close()
        print(colored(f"[{SUCCESS_ICON}] {testName}", "green"))
    except Exception as err:
        print(colored(f"[{FAILURE_ICON}] {testName}:\n", "red"), end="")
        print(err)


def testAll():
    tests = os.listdir(INPUT_DIR)
    for testName in tests:
        if testName[0] == ".":
            continue
        if not os.path.isfile(INPUT_DIR + testName):
            print(colored(f"[{FAILURE_ICON}] {testName}: Invalid File", "red"))
        testOne(testName)


def testOne(testName: str):
    input, output = getInputOutput(testName)
    test(testName, input, output)


def main():
    if sys.argv.__len__() > 1:
        PORT = sys.argv[1]
    testAll()


if __name__ == "__main__":
    main()
