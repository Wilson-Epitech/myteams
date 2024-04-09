#!/usr/bin/env python3


import os
import sys
import telnetlib
import subprocess as sb
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
                    input.append(tmp_i[i])
                    try:
                        output.append(tmp_o[i - imports])
                    except:
                        print(f"Invalid Test File:{filename}")
                        exit(1)
            return input, output


def test(testName: str, input: list[str], output: list[str]):
    CONNECTION_SUCCESS = "client accepted"
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
        got = client.read_until(CONNECTION_SUCCESS.encode(), TIMEOUT)
        
        if got != CONNECTION_SUCCESS.encode():
            client.close()
            raise ValueError(
                    colored(f" > ", on_color="on_blue")
                    + colored(f" {str("connection message".encode())[2:-1]}\n", "blue")
                    + colored(f" + ", on_color="on_green")
                    + colored(f" {str(CONNECTION_SUCCESS)[:-1]}\n", "green")
                    + colored(f" - ", on_color="on_red")
                    + colored(f" {str(got)[2:-1]}\n", "red")
                )

        for i in range(len(input)):
            if input[i].startswith(". "):
                sb.run(input[i][2:], shell=True)
                continue
            expected = f"{output[i]}\n".encode()
            client.write(f"{input[i]}\n".encode())
            got = client.read_until(expected, TIMEOUT)
            if expected != got:
                client.close()
                raise ValueError(
                    colored(f" > ", on_color="on_blue")
                    + colored(f" {str(input[i].encode())[2:-1]}\n", "blue")
                    + colored(f" + ", on_color="on_green")
                    + colored(f" {str(expected)[2:-1]}\n", "green")
                    + colored(f" - ", on_color="on_red")
                    + colored(f" {str(got)[2:-1]}\n", "red")
                )
        client.close()
        print(colored(f"[{SUCCESS_ICON}] {testName}", "green"))
    except Exception as e:
        print(colored(f"[{FAILURE_ICON}] {testName}:\n", "red"), end="")
        print(e)


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
        testOne(sys.argv[1])
    else:
        testAll()


if __name__ == "__main__":
    main()
