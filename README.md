```markdown
# Philosophers - 42 School Project

## 📋 Description
Philosophers est un projet avancé du tronc commun à 42 qui aborde les problèmes de programmation concurrente et de synchronisation. Le projet implémente la solution au problème classique des "Dining Philosophers" en utilisant les threads et les mutex.

## 🎯 Objectifs
- Comprendre la programmation multithreadée
- Maîtriser les mécanismes de synchronisation (mutex, sémaphores)
- Résoudre les problèmes de concurrence (interblocage, famine)
- Implémenter un système de gestion du temps précis

## 🛠️ Technologies Utilisées

### 🔧 Synchronisation
- **Threads POSIX** - pthread_create, pthread_join
- **Mutex** - Verrous pour accès exclusif aux ressources
- **Sémaphores** - Synchronisation avancée (version bonus)

### ⏱️ Gestion du Temps
- **Timestamps précis** - gettimeofday()
- **Attentes contrôlées** - usleep() avec vérification
- **Monitoring en temps réel** - Affichage des états

## 🚀 Installation et Utilisation

### 📋 Compilation
```bash
git clone [URL-du-repository]
cd philosophers
make
```

### ⚙️ Utilisation
```bash
# Version obligatoire (threads + mutex)
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]

# Version bonus (processus + sémaphores)
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

## 📊 Fonctionnalités Implémentées

### 🧠 Logique des Philosophes
- **Cycle de vie** : Penser → Prendre fourchettes → Manger → Dormir
- **Gestion des fourchettes** - Ressources partagées critiques
- **Détection de la mort** - Monitoring continu de chaque philosophe
- **Limite de repas** - Optionnel, arrêt après N repas

### 🛡️ Synchronisation
- **Protection des données partagées** - Mutex sur l'état des philosophes
- **Prévention des interblocages** - Ordre d'acquisition des fourchettes
- **Éviter la famine** - Stratégie équitable d'accès aux ressources

### ⚡ Version Bonus
- **Processus légers** - fork() au lieu de pthread_create()
- **Sémaphores système** - sem_open(), sem_wait(), sem_post()
- **Mémoire partagée** - shm_open() pour l'état global

## 💡 Compétences Développées
- Programmation concurrente avancée
- Gestion des races conditions
- Prévention des interblocages (deadlocks)
- Synchronisation de processus/threads
- Gestion précise du temps système
- Débogage multithreadé complexe
- Optimisation des performances

## 🎯 Paramètres du Programme

### 📝 Arguments
- **number_of_philosophers** : Nombre de philosophes et de fourchettes
- **time_to_die** : Temps maximum sans manger (ms)
- **time_to_eat** : Temps pour manger (ms)
- **time_to_sleep** : Temps pour dormir (ms)
- **number_of_meals** : (Optionnel) Nombre de repas avant arrêt

### 🔍 Exemple
```bash
# 5 philosophes, meurent après 800ms sans manger
./philo 5 800 200 200

# Avec limite de 7 repas par philosophe
./philo 5 800 200 200 7
```

## 📁 Structure du Projet
```
philo/
├── srcs             # Threads + mutex
├── inc/             # Fichiers d'en-tête
├── Makefile         # Compilation des deux versions
└── README.md        # Documentation
```

Ce projet est essentiel pour comprendre les défis de la programmation concurrente et prépare aux développements d'applications temps réel et systèmes distribués.
```
