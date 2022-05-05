# 🗃️ Plan

[Notion](https://agatocherry.notion.site/Minishell-d9d2a462a1384b26ae9491338da6e053) 📌

Agathe :
- Vérifier les retours pour chaque cas d'erreurs
- Rechercher quelques commandes fourbes et les tester (sauf les pipes pas encore prêtes)
  - "echo &@agathe" ne fonctionne pas (les caracteres speciaux)
  - "exit 123 123" dois etre une erruer (exit
bash: exit: too many arguments)
  - "cd cd" est censer revenir a $HOME
  - "unset PATH" n'unset pas reellement $PATH

Shellen :
- Finaliser les pipes
- Leaks
- Mettre en place "./minishell -c" pour les testers

Délai : Rendre au plus tard le 6 Mai
