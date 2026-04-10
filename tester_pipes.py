import subprocess

def run_test(command):
    p = subprocess.Popen(['./minishell'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    input_str = f"{command}\nexit\n"
    stdout, stderr = p.communicate(input=input_str)
    return stdout

tests = [
    "cat | cat | cat | ls",
    "ls | exit",
    "ls | exit 42",
    "exit | ls",
    "echo hola | cat -e",
    "pwd | echo hola",
]

for cmd in tests:
    out = run_test(cmd)
    print(f"--- Command: {cmd} ---")
    print(out)
    print("-" * 30)

