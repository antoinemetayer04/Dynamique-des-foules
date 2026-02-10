clear; clc;

%% Chargement des données
data = readtable('resultats.csv');

% Extraction des paramètres t et id
ids = unique(data.id);
temps = unique(data.t);
nb_indiv = length(ids);

%% Configuration de la fenêtre graphique
figure('Color', 'w', 'Name', 'Simulation : Points Individuels');
hold on; 
grid on; 
axis equal;
xlabel('Position X (m)'); 
ylabel('Position Y (m)');

% Définition des limites des axes
axis([min(data.x)-2 max(data.x)+2 min(data.y)-2 max(data.y)+2]); 

% Tracé du mur
line([-5 15], [0 0], 'Color', 'k', 'LineWidth', 2, 'HandleVisibility', 'off');

% Initialisation des points
h = gobjects(nb_indiv, 1);
couleurs = lines(nb_indiv); % Génère des couleurs distinctes

for i = 1:nb_indiv
    % On initialise le point à une position invisible (NaN)
    h(i) = plot(NaN, NaN, 'o', 'MarkerSize', 8, 'MarkerFaceColor', couleurs(i,:), 'MarkerEdgeColor', 'k');
end

%% Boucle graphique
for k = 1:length(temps)
    t_actuel = temps(k);
    
    % Pour chaque individu, on met à jour sa position
    for i = 1:nb_indiv
        % Extraction de la ligne correspondant à l'individu i au temps t
        idx = (data.t == t_actuel & data.id == ids(i));
        
        if any(idx)
            nouvelle_x = data.x(idx);
            nouvelle_y = data.y(idx);
            
            % Actualisation de la fenêtre
            set(h(i), 'XData', nouvelle_x, 'YData', nouvelle_y);
        end
    end
    
    % Titre dynamique en temps
    title(sprintf('Temps : %.2f s', t_actuel));
    
    % Force l'affichage immédiat
    drawnow;
end