# 🗃️ Plan

[Notion](https://agatocherry.notion.site/Minishell-d9d2a462a1384b26ae9491338da6e053) 📌

Agathe :
- Vérifier les retours pour chaque cas d'erreurs
- Rechercher quelques commandes fourbes et les tester (sauf les pipes pas encore prêtes)
  - "unset PATH" n'unset pas reellement $PATH
  - "echo $REPL_OWNER" ne fonctionne pas
- Leaks 

Problèmes non réglés :
- < Makefile cat (leaks)
- echo "hello" >> test | ls ("hello" n'est pas dans le fichier test)
- retour d'erreur quand sigint dans heredoc

Délai : Rendre au plus tard le 6 Mai
