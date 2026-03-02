# Plan de Projet Détaillé pour Minishell (42)

Ce document a pour but de fournir un plan structuré pour aborder le projet Minishell. Il est basé sur le sujet officiel et les bonnes pratiques partagées par d'anciens étudiants.

## Phase 0 : Pré-requis, Stratégie et Compréhension

L'objectif est de créer un shell simple, un "mini-bash". Avant d'écrire la moindre ligne de code, il est crucial de maîtriser certains concepts et de définir une stratégie de travail.

### 1. Concepts Clés à Maîtriser :
- **Processus** : `fork()`, `wait()`, `waitpid()`, `execve()`. Comprendre la différence entre processus parent et enfant est fondamental.
- **Descripteurs de Fichiers (File Descriptors)** : `open()`, `read()`, `write()`, `close()`. Savoir ce que sont `STDIN_FILENO` (0), `STDOUT_FILENO` (1), et `STDERR_FILENO` (2).
- **Pipes et Redirections** : `pipe()`, `dup()`, `dup2()`. C'est le cœur de la communication entre les commandes.
- **Signaux** : `signal()`, `sigaction()`, `kill()`. Comprendre comment le système d'exploitation communique des événements aux processus.
- **Variables d'environnement** : `getenv()`, `setenv()` (même si non autorisée, comprendre le concept), et la variable `char **envp`.

### 2. Outils et Organisation du Travail :
- **Gestion de version (Git)** : Indispensable, surtout en binôme.
  - Créez un dépôt sur GitHub ou l'intranet.
  - Prenez l'habitude : `git pull` avant de commencer, `git commit` régulièrement avec des messages clairs, `git push` à la fin de chaque session.
  - Utilisez des branches pour les fonctionnalités complexes afin de ne pas casser la version principale (`main` ou `master`).
- **Communication** : La clé du succès en binôme.
  - Faites du *peer programming* au début de chaque grande étape (parsing, exécution).
  - Expliquez votre code à votre partenaire. Si vous ne pouvez pas l'expliquer, c'est que vous ne le maîtrisez pas complètement.
- **Tests** :
  - Pour tester le comportement attendu, lancez bash en mode POSIX : `bash --posix`. Votre shell doit se comporter comme lui, et non comme votre `zsh` ou `bash` par défaut.
  - Créez des scripts de test simples pour chaque fonctionnalité.

### 3. Analyse du Sujet :
- **Fonctions Autorisées** : Gardez la liste (page 8 du sujet) sous les yeux. Si une fonction n'y est pas, vous ne pouvez pas l'utiliser.
- **Variable Globale** : Le sujet est strict : **UNE SEULE** variable globale est autorisée, uniquement pour stocker un signal reçu (ex: `volatile sig_atomic_t g_signal_status;`). N'essayez pas de contourner cette règle.

---

## Phase 1 : La Boucle Principale et la Lecture de l'Input

C'est le squelette de votre shell.

1.  **Créer le `main`** avec une boucle infinie (`while (1)`).
2.  **Afficher un prompt** et lire l'entrée utilisateur en utilisant `readline()`.
3.  **Gérer l'historique** : Ajoutez chaque ligne lue (non vide) à l'historique avec `add_history()`.
4.  **Gérer `Ctrl-D` (EOF)** : `readline()` retournera `NULL`. C'est le signal pour quitter le shell proprement. Affichez "exit" et quittez.
5.  **Gestion de ligne vide** : Si l'utilisateur appuie sur Entrée sans rien taper, la boucle doit simplement continuer et ré-afficher le prompt.

---

## Phase 2 : Parsing (Analyse de la ligne de commande)

C'est la partie la plus complexe et la plus importante. Un bon parsing rendra l'exécution beaucoup plus simple.

### 1. Lexer (Tokenisation)
- **Objectif** : Transformer la chaîne de caractères de `readline` en une liste de "tokens" (mots).
- **Implémentation** :
  - Parcourez la chaîne et découpez-la en fonction des espaces et des méta-caractères (`|`, `<`, `>`).
  - **Gestion des quotes** :
    - Si vous rencontrez une quote (`'` ou `"`), tout ce qui suit jusqu'à la quote fermante correspondante fait partie du même token.
    - Il faut gérer les quotes non fermées (comportement indéfini selon le sujet, mais il faut le gérer pour ne pas crasher).
  - Le résultat pourrait être une liste chaînée de tokens, où chaque maillon contient la chaîne du token et son type (mot, pipe, redirection, etc.).

### 2. Expansion
- **Objectif** : Remplacer les variables (`$VAR`, `$?`) par leur valeur.
- **Implémentation** :
  - Après le lexer, parcourez votre liste de tokens.
  - Pour chaque token, vérifiez s'il contient un `$`.
  - Si c'est le cas (et qu'il n'est pas entre quotes simples `'`), remplacez-le par la valeur de la variable d'environnement (`getenv()`) ou par le code de retour de la dernière commande pour `$?`.

### 3. Parser
- **Objectif** : Transformer la liste de tokens en une structure de données exécutable, souvent un **Arbre de Syntaxe Abstraite (AST)**.
- **Structure** :
  - L'AST peut être une structure où les nœuds sont des commandes et les feuilles sont les arguments. Les pipes (`|`) peuvent être des nœuds parents qui lient deux sous-arbres de commandes.
  - Exemple : `ls -l | wc -l` pourrait être un nœud `PIPE` avec à gauche un nœud `COMMANDE` (`ls`, `-l`) et à droite un nœud `COMMANDE` (`wc`, `-l`).
  - Chaque nœud de commande doit aussi contenir des informations sur ses redirections.

---

## Phase 3 : Exécution

C'est ici que l'AST prend vie.

### 1. Exécuteur de commandes simples
- Parcourez l'arbre. Pour chaque commande :
  1. `fork()` pour créer un processus enfant.
  2. **Dans l'enfant** :
     - Gérez les redirections avec `dup2()` si nécessaire.
     - Utilisez `execve()` pour lancer la commande. Vous devez construire le chemin complet de l'exécutable (en cherchant dans le `PATH`) et lui passer les arguments (`argv`).
  3. **Dans le parent** :
     - `waitpid()` pour attendre que l'enfant se termine.
     - Stockez le code de retour de l'enfant pour pouvoir le restituer via `$?`.

### 2. Implémentation des built-ins
- Certaines commandes **doivent** être exécutées par le processus parent car elles modifient l'état du shell lui-même.
  - `cd` : Doit changer le répertoire du shell parent.
  - `export` : Doit modifier l'environnement du shell parent.
  - `unset` : Doit modifier l'environnement du shell parent.
  - `exit` : Doit faire quitter le shell parent.
- Les autres (`echo`, `pwd`, `env`) peuvent être implémentées comme des built-ins mais peuvent aussi être lancées dans un processus enfant. Il est plus simple de les coder directement.

---

## Phase 4 : Pipes et Redirections

C'est une extension de la phase d'exécution.

### 1. Pipes (`|`)
- Si votre nœud AST est un pipe :
  1. Créez un pipe avec `pipe()`.
  2. `fork()` une première fois pour le processus de gauche.
     - Dans cet enfant, `dup2()` la sortie standard (`STDOUT_FILENO`) sur l'extrémité d'écriture du pipe. Exécutez la commande.
  3. `fork()` une seconde fois pour le processus de droite.
     - Dans cet enfant, `dup2()` l'entrée standard (`STDIN_FILENO`) sur l'extrémité de lecture du pipe. Exécutez la commande.
  4. Dans le parent, fermez les deux extrémités du pipe et attendez la fin des deux enfants.

### 2. Redirections (`<`, `>`, `>>`) et Heredoc (`<<`)
- Avant d'`execve` dans l'enfant :
  - Pour `<`, ouvrez le fichier en lecture et `dup2()` son fd sur `STDIN_FILENO`.
  - Pour `>`, ouvrez le fichier en écriture (en le créant/tronquant) et `dup2()` son fd sur `STDOUT_FILENO`.
  - Pour `>>`, ouvrez le fichier en mode "append" et `dup2()` son fd sur `STDOUT_FILENO`.
  - Pour `<<` (Heredoc), lisez l'entrée jusqu'au délimiteur. Le plus simple est de stocker cela dans un pipe et de `dup2()` la lecture de ce pipe sur `STDIN_FILENO`.

---

## Phase 5 : Gestion des Signaux

- Utilisez `sigaction()` pour intercepter les signaux.
- **`ctrl-C` (`SIGINT`)** :
  - Le handler de signal doit mettre à jour votre variable globale (ex: `g_signal_status = SIGINT;`).
  - Dans votre boucle principale, après `readline`, vérifiez la valeur de cette variable. Si elle indique qu'un `SIGINT` a été reçu, réinitialisez la variable et affichez un nouveau prompt.
- **`ctrl-` (`SIGQUIT`)** : Le handler ne doit rien faire en mode interactif.
- **`ctrl-D`** : Ce n'est pas un signal, mais la fin d'un flux (EOF), géré directement par `readline()`.

---

## Phase 6 : Nettoyage et Bonus

- **Fuites Mémoire** : Une fois que tout fonctionne, utilisez `valgrind` ou les `leaks` de macOS pour traquer et éliminer toutes les fuites mémoire. Chaque `malloc` doit avoir son `free`.
- **Bonus** : Si et seulement si la partie obligatoire est parfaite, vous pouvez implémenter :
  - Les opérateurs logiques `&&` et `||`.
  - Les wildcards (`*`).
