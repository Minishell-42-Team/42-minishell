import subprocess
import os

def run_test(command):
    process = subprocess.Popen(['./minishell'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate(input=command + "\nexit\n")
    # On cherche le code de retour après la commande
    # Note: On ajoute 'exit' pour fermer le shell proprement
    # Pour obtenir le code de retour de la commande précédente, on peut essayer d'envoyer 'echo $?'
    process_exit = subprocess.Popen(['./minishell'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout_exit, stderr_exit = process_exit.communicate(input=command + "\necho $?\nexit\n")
    
    return stdout_exit, stderr_exit

tests = [
    ("", "Entrée vide"),
    ("   ", "Espaces seuls"),
    ("\t\t", "Tabulations seules"),
    (":", ":"),
    ("!", "!"),
    (">", ">"),
    ("<", "<"),
    (">>", ">>"),
    ("<<", "<<"),
    ("<>", "<>"),
]

for cmd, desc in tests:
    out, err = run_test(cmd)
    print(f"--- Test: {desc} ('{cmd}') ---")
    print(f"STDOUT:\n{out}")
    print(f"STDERR:\n{err}")
    print("-" * 40)

