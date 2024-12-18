# 🎩 **Cub3D - Mon premier RayCaster avec la minilibX**

Cub3D est une implémentation simplifiée d'un moteur de rendu 3D inspiré de *Wolfenstein 3D*. Ce projet utilise la **minilibX** pour le rendu graphique et propose une expérience de RayCasting avec un affichage en temps réel. L'objectif est de maîtriser les bases de la gestion des fenêtres, du rendu de textures et du mouvement en 3D.

---

## 📋 **Sommaire**

1. [Fonctionnalités](#fonctionnalités)
2. [Dépendances](#dépendances)
3. [Compilation et exécution](#compilation-et-exécution)
4. [Fichier `.cub` de description](#fichier-cub-de-description)
5. [Contrôles](#contrôles)
6. [Gestion des erreurs](#gestion-des-erreurs)
7. [Exemple](#exemple)
8. [Médias](#médias)

---

## 🛠️ **Fonctionnalités**

- 📝 **Lecture de fichiers `.cub`** pour configurer la scène.
- 🖼 **Textures** différentes pour chaque orientation (Nord, Sud, Est, Ouest).
- 🏞️ **Couleurs personnalisables** pour le sol et le plafond.
- 🟡️ **Gestion complète de la fenêtre**, incluant :
  - Minimisation
  - Fermeture propre en cas de clic sur la croix rouge (`X`)
- 🎮 **Mouvement fluide** de la caméra avec des contrôles intuitifs.

---

## 🧪 **Dépendances**

Pour compiler et exécuter **Cub3D**, vous avez besoin des éléments suivants :

- **minilibX** : disponible sur votre OS ou à compiler depuis ses sources.
- **Make** et **GCC** (ou un autre compilateur compatible avec `clang`).

**Installation de la minilibX** (si nécessaire) :

```bash
git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux
make
```

---

## ⚙️ **Compilation et exécution**

1. **Cloner le projet** :

   ```bash
   git clone <url-du-repo>
   cd Cub3D
   ```

2. **Compiler** le programme :

   ```bash
   make
   ```

3. **Exécuter** avec un fichier `.cub` :

   ```bash
   ./cub3D path/to/map.cub
   ```

---

## 🛡️ **Fichier `.cub` de description**

Le fichier `.cub` doit contenir les informations suivantes :

1. **Textures** pour chaque direction :
   ```text
   NO ./path_to_the_north_texture
   SO ./path_to_the_south_texture
   WE ./path_to_the_west_texture
   EA ./path_to_the_east_texture
   ```

2. **Couleurs** pour le sol et le plafond :
   ```text
   F 220,100,0   # Sol
   C 225,30,0    # Plafond
   ```

3. **Carte** de la scène :
   - `1` : Mur
   - `0` : Espace vide
   - `N`, `S`, `E`, `W` : Position de départ du joueur et son orientation.

   Exemple de fichier `.cub` complet :

   ```text
   NO ./textures/north_texture.xpm
   SO ./textures/south_texture.xpm
   WE ./textures/west_texture.xpm
   EA ./textures/east_texture.xpm
   F 220,100,0
   C 225,30,0

   111111
   100101
   101001
   1100N1
   111111
   ```

---

## 🎮 **Contrôles**

- **Rotation de la caméra** :
  - ➡️ **Flèche droite** : Regarder à droite
  - ⬅️ **Flèche gauche** : Regarder à gauche

- **Déplacement** :
  - **W** : Avancer
  - **S** : Reculer
  - **A** : Aller à gauche
  - **D** : Aller à droite

- **Quitter** :
  - **ESC** : Quitter proprement
  - **Cliquez sur la croix rouge (`X`)** : Fermer la fenêtre

---

## 🚨 **Gestion des erreurs**

Le programme quitte avec un message d'erreur si :

- Le fichier `.cub` est mal formaté.
- La carte n'est pas entourée de murs (`1`).
- Une texture ou une couleur est manquante ou incorrecte.

**Exemple d'erreur** :

```text
Error
Invalid map configuration
```

---

## 📝 **Exemple**

```bash
./cub3D maps/example.cub
```

---

## 🎬 **Médias**

### 🎞️ **Captures d'écran**

![Capture d'écran 1](https://github.com/SolDavid76/cub3d/blob/main/screenshots/2.png)
![Capture d'écran 2](https://github.com/SolDavid76/cub3d/blob/main/screenshots/1.png)

### 🎥 **Vidéo de démonstration**

[![Vidéo de démo](path/to/demo_thumbnail.png)](path/to/demo_video.mp4)

---

## 📚 **Licence**

Ce projet est sous licence MIT.

