import subprocess
import time
import os
import signal

def run_test():
    p = subprocess.Popen(['./minishell'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    # On lance sleep
    p.stdin.write("sleep 2\n")
    p.stdin.flush()
    
    # On attend un peu que sleep soit lancé
    time.sleep(0.5)
    
    # On envoie SIGINT (Ctrl+C) au processus minishell
    p.send_signal(signal.SIGINT)
    
    # On demande le code de retour
    p.stdin.write("echo $?\n")
    p.stdin.write("exit\n")
    p.stdin.flush()
    
    stdout, stderr = p.communicate()
    return stdout

print(run_test())
