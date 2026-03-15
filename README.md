# Dynamique des Foules

## Description

Ce projet implémente une simulation de la dynamique des foules en C++ utilisant le modèle de Helbing et Molnar. Il simule le comportement d'individus dans un environnement avec des murs, en tenant compte des forces sociales, de la compression et du frottement. La simulation génère des données qui peuvent être visualisées avec MATLAB.

Le projet comprend différents modes de simulation :
- Sortie simple
- Sortie avec obstacle
- Croisement de foules

Différents modes de calcul :
- Mise à jour globale des forces de chaque individu puis mise à jour des vitesses et positions de chaque individu (calculer_algo_1)
- Pour chaque individu, calcul des forces puis mise à jour des vitesses et positions (calculer_algo_2)

Et différents niveaux de stress :
- Calme
- Normal
- Flux dense
- Panique

Toutes ces possibilités sont sélectionnables dans le fichier `src/main.cpp`

## Paramètres Physiques

Le modèle utilise les paramètres suivants (basés sur Helbing) :
- **k1** : Constante de compression (100000 N - 150000 N)
- **k2** : Constante de frottement (200000 N - 305000 N)
- **A** : Force sociale (500 N - 5000 N)
- **B** : Rayon d'interaction sociale (0.05 m - 0.2 m)

## Utilisation du Makefile

### Compilation
Pour compiler le projet, exécutez la commande suivante dans le répertoire racine :
```bash
make all
```

Cela générera l'exécutable `dynamique-des-foules.x`.

### Nettoyage
Pour nettoyer les fichiers compilés :
```bash
make clean
```

Pour un nettoyage complet incluant l'exécutable :
```bash
make realclean
```

### Exécution
Pour exécuter la simulation :
```bash
make run
```
(A noter que cette commande compile aussi le code, ce qui exempte de la commande make all.)

Ou directement :
```bash
./dynamique-des-foules.x
```

Les résultats seront sauvegardés dans le dossier `results/` dans les fichiers `results/murs.csv` et `results/resultats.csv`.

## Visualisation

Les résultats peuvent être visualisés en utilisant le script MATLAB `Visualisation.m` dans le dossier `results/`.

Vous devez suivre les informations contenues dans le fichier MATLAB concernant la sélection de fichiers à visualiser. 

## Auteurs

Louise Hope-Rapp, Antoine Métayer, Vincent Bardaro
