import subprocess

def run_test(commands):
    p = subprocess.Popen(['./minishell'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    input_str = "\n".join(commands) + "\nexit\n"
    stdout, stderr = p.communicate(input=input_str)
    return stdout, stderr

print("--- Test 1: export HOLA=bonjour ---")
out, err = run_test(["export HOLA=bonjour", "env | grep HOLA"])
print(out)

print("--- Test 2: export identifiants invalides ---")
out, err = run_test(["export 9HOLA=val", "export =", "export %"])
print(out)
print("STDERR (Erreurs attendues):")
print(err)

print("--- Test 3: unset HOLA ---")
out, err = run_test(["export HOLA=bonjour", "unset HOLA", "env | grep HOLA"])
print("Output (vide attendu):")
print(out)
