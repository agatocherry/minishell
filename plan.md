# 🗃️ Plan

[Notion](https://agatocherry.notion.site/Minishell-d9d2a462a1384b26ae9491338da6e053) 📌

- [x] Initialiser l'env, la structure shell (et le signal ?)
- [x] Ecrire le prompt
- [x] Récuperer la ligne avec get_next_line
- [x] Réaliser un parsing de la ligne dans une liste chainée et lui donner un type
- [x] Envoyer vers la bonne fonction suivant le type de la commande
- [x] Répéter dans une boucle infini jusqu'à SIGINT
- [x] Faire l'historique
- [ ] Incrémenter le niveau du shell -> Shellen
- [ ] Gérer les expansions -> Shellen
- [ ] Gérer ctrl-\ -> Shellen ou Agathe
- [ ] Améliorer check_command -> Shellen
- [ ] Faire un fichier de commandes utils (has pipe | has_redir | has_type | ...) -> Shellen ou Agathe
- [ ] Faire un env par défaut sur l'env est effacé -> Agathe
- [x] Clear la commande depuis le début
- [x] Faire clear_env (une commande qui appelle 2d arrays pour free env et path_env)
- [ ] Gérer la redirection vers différents fichiers (fonction reçoit un pointeur sur t_shell et lie le fd_in et le fd_out si besoin) -> Agathe ?
- [ ] Fonction qui redirige vers la fonction des commandes -> Shellen
- [ ] Pipe -> Agathe
