# Routine Git Quotidienne pour le Projet Minishell

Ce document décrit un workflow Git simple et efficace, spécialement pensé pour une équipe de deux. L'objectif est de garder un historique propre, de faciliter la collaboration et de minimiser les conflits.

---

### 1. Au Début de Chaque Session de Travail

Avant d'écrire la moindre ligne de code, assurez-vous d'être à jour.

```bash
# 1. Allez sur la branche principale
git checkout main

# 2. Récupérez les dernières modifications fusionnées par votre partenaire
git pull
```
**Pourquoi ?** Pour être sûr de démarrer votre travail sur la version la plus récente du projet.

---

### 2. Pour Commencer une Nouvelle Tâche (Fonctionnalité ou Correction)

**Ne travaillez JAMAIS directement sur la branche `main`.**

```bash
# 1. Créez une nouvelle branche dédiée à votre tâche
git checkout -b <type>/<nom-descriptif>
```

-   `<type>` peut être `feature` (pour une nouvelle fonctionnalité) ou `fix` (pour une correction).
-   `<nom-descriptif>` doit être court et clair.

**Exemples :**
```bash
git checkout -b feature/parsing-redirections
git checkout -b fix/leak-in-execution
```

**Pendant que vous travaillez :**
Faites des petits commits, clairs et fréquents.

```bash
# Ajoutez vos fichiers modifiés
git add .

# Créez un "point de sauvegarde" avec un message clair
git commit -m "feat: Gère la redirection d'input (<)"
```

---

### 3. Quand Votre Tâche est Terminée et Testée

Il est temps de proposer votre travail pour qu'il soit intégré à la branche `main`. C'est là qu'intervient la **Pull Request (PR)**.

**1. Poussez votre branche sur GitHub :**
```bash
# Remplacez <nom-de-votre-branche> par le vrai nom
git push origin <nom-de-votre-branche>
```

**2. Créez la Pull Request :**
   - Allez sur la page de votre dépôt GitHub.
   - Un bandeau devrait apparaître pour vous proposer de créer une PR à partir de votre branche fraîchement poussée.
   - Cliquez, donnez un titre clair et une brève description de ce que vous avez fait.
   - Assignez votre partenaire comme **"Reviewer"**.

**3. Faites la Relecture de Code (Code Review) :**
   - Votre partenaire reçoit une notification. Il doit relire votre code et peut laisser des commentaires.
   - Si des modifications sont nécessaires, faites de nouveaux commits sur votre branche et poussez-les (`git push`). La PR se mettra à jour automatiquement.
   - La discussion se fait dans l'interface de la PR.

**4. Fusionnez la Pull Request :**
   - Une fois que le "reviewer" a approuvé les changements ("Approve"), vous pouvez cliquer sur le bouton vert **"Merge pull request"** sur GitHub.
   - Votre code fait maintenant partie de la branche `main` !

---

### 4. Après la Fusion d'une PR

Une fois qu'une PR a été fusionnée dans `main` (la vôtre ou celle de votre partenaire), tout le monde doit mettre à jour sa version locale de `main`.

```bash
# 1. Allez sur votre branche principale locale
git checkout main

# 2. Récupérez la nouvelle version de main qui inclut la PR fusionnée
git pull
```

Vous êtes maintenant prêt à commencer une nouvelle tâche en créant une nouvelle branche à partir de ce `main` à jour.

---

### Résumé Visuel du Workflow

1.  `git pull` (sur `main`)
2.  `git checkout -b feature/ma-super-feature`
3.  *... Travail et commits ...*
4.  `git push origin feature/ma-super-feature`
5.  Ouvrir une Pull Request sur GitHub.
6.  Relecture et Approbation.
7.  Merge de la PR sur GitHub.
8.  Retour à l'étape 1.
