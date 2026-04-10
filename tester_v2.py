import subprocess
import os

def run_minishell(command):
    p = subprocess.Popen(['./minishell'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    # On ajoute echo $? pour récupérer le statut global après la commande
    # Note: On utilise un séparateur unique pour isoler la sortie
    input_str = f"{command}\necho 'STATUS_SEPARATOR'\necho $?\nexit\n"
    stdout, stderr = p.communicate(input=input_str)
    
    parts = stdout.split('STATUS_SEPARATOR')
    if len(parts) > 1:
        cmd_out = parts[0].replace('minishell> ', '').strip()
        status = parts[1].strip().split('\n')[0]
        return cmd_out, stderr.strip(), status
    return stdout, stderr, "Unknown"

def run_bash(command):
    # On lance bash avec la commande
    p = subprocess.Popen(['bash'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    input_str = f"{command}\necho 'STATUS_SEPARATOR'\necho $?\nexit\n"
    stdout, stderr = p.communicate(input=input_str)
    
    parts = stdout.split('STATUS_SEPARATOR')
    if len(parts) > 1:
        cmd_out = parts[0].strip()
        status = parts[1].strip().split('\n')[0]
        return cmd_out, stderr.strip(), status
    return stdout, stderr, "Unknown"

test_cases = [
    # Syntaxe (Page 1 & 2)
    "",
    "   ",
    ":",
    "!",
    ">",
    "<",
    ">>",
    "<<",
    "<>",
    ">>>>>",
    "|",
    "||",
    "&&",
    "\"\"",
    "''",
    # Built-ins (Page 3)
    "echo",
    "echo -n Hola",
    "pwd",
    "cd .",
    "export ABC=hola",
    "unset ABC",
    "env",
]

print(f"{'Command':<25} | {'Shell Out':<15} | {'Bash Out':<15} | {'Shell $?':<8} | {'Bash $?':<8} | {'Result'}")
print("-" * 100)

for cmd in test_cases:
    m_out, m_err, m_status = run_minishell(cmd)
    b_out, b_err, b_status = run_bash(cmd)
    
    # On simplifie les sorties pour l'affichage
    m_out_disp = (m_out[:12] + '..') if len(m_out) > 15 else m_out
    b_out_disp = (b_out[:12] + '..') if len(b_out) > 15 else b_out
    
    success = (m_status == b_status)
    res = "OK" if success else "KO"
    
    print(f"{cmd:<25} | {m_out_disp:<15} | {b_out_disp:<15} | {m_status:<8} | {b_status:<8} | {res}")

