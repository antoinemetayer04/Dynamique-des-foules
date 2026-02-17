clear; clc;

%% Chargement des données
data_foule = readtable('resultats_aleatoires.csv');
data_murs = readtable('murs.csv');

% Extraction des paramètres t et id
ids = unique(data_foule.id);
temps = unique(data_foule.t);
nb_indiv = length(ids);

%% Configuration de la fenêtre graphique
figure('Color', 'w', 'Name', 'Simulation : Points Individuels');
hold on; 
grid on; 
axis equal;
xlabel('Position X (m)'); 
ylabel('Position Y (m)');

% Définition des limites des axes
all_x = [data_murs.x1; data_murs.x2];
all_y = [data_murs.y1; data_murs.y2];
axis([min(all_x)-1 max(all_x)+1 min(all_y)-1 max(all_y)+1]); 

% Tracé du mur
for j = 1:height(data_murs)
    % On trace le segment entre (x1, y1) et (x2, y2)
    line([data_murs.x1(j) data_murs.x2(j)], ...
         [data_murs.y1(j) data_murs.y2(j)], ...
         'Color', [0.2 0.2 0.2], 'LineWidth', 3, 'HandleVisibility', 'off');
    
    % On calcule le milieu du segment pour placer la flèche (pour tester les résultats)
    mx = (data_murs.x1(j) + data_murs.x2(j)) / 2;
    my = (data_murs.y1(j) + data_murs.y2(j)) / 2;
    quiver(mx, my, data_murs.Nx(j)*0.5, data_murs.Ny(j)*0.5, ...
           'Color', 'r', 'MaxHeadSize', 0.5, 'AutoScale', 'off');
end

% Initialisation des points
h = gobjects(nb_indiv, 1);
couleurs = lines(nb_indiv); % Génère des couleurs distinctes

t_debut = temps(1); % On récupère le premier instant T

for i = 1:nb_indiv
    % 1. Trouver la position initiale (t=0) de cet individu
    idx_init = (abs(data_foule.t - t_debut) < 1e-5 & data_foule.id == ids(i));

    if any(idx_init)
        x0 = data_foule.x(idx_init);
        y0 = data_foule.y(idx_init);
        r0 = data_foule.r(idx_init);
        
        % On crée un rectangle avec Curvature [1 1] pour faire un cercle
        % Position = [x-r, y-r, 2*r, 2*r]
        h(i) = rectangle('Position', [x0-r0, y0-r0, 2*r0, 2*r0], ...
                         'Curvature', [1 1], ...
                         'FaceColor', couleurs(i,:), ...
                         'EdgeColor', 'k');
    else
        % Sécurité au cas où l'individu n'existe pas à t=0
        h(i) = rectangle('Position', [0, 0, 0.1, 0.1], 'Visible', 'off');
    end
end

%% Boucle graphique
for k = 1:length(temps)
    t_actuel = temps(k);
    
    % Pour chaque individu, on met à jour sa position
    for i = 1:nb_indiv
        % Extraction de la ligne correspondant à l'individu i au temps t
        idx = (data_foule.t == t_actuel & data_foule.id == ids(i));
        
        if any(idx)
            nx = data_foule.x(idx);
            ny = data_foule.y(idx);
            nr = data_foule.r(idx);
            
            % Actualisation de la fenêtre
            set(h(i), 'Position', [nx-nr, ny-nr, 2*nr, 2*nr]);
        end
    end
    
    % Titre dynamique en temps
    title(sprintf('Temps : %.2f s', t_actuel));
    
    % Force l'affichage immédiat
    drawnow;
end