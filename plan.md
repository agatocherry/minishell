# 🗃️ Plan

[Notion](https://agatocherry.notion.site/Minishell-d9d2a462a1384b26ae9491338da6e053) 📌

- J'ai vu que cat wouaf renvoie 256 alors que ça devrait renvoyer 1, si jamais tu trouves d'où vient l'erreur

A tester :
- Verifier que $? est identique a bash pour chaque erreur : 
  - de parsing
  - de commandes type ls cat (sans erreur mais aussi avec une erreur unknwon command, access denied, is directory et no such file or directory)
  - de builtins (quand il y a une erreur et quand il n'y a pas d'erreur)
  - après chaque sigint (dans heredoc, avant d'appuyer sur entrée et après avoir appuyer sur entrée avec une boucle infinie comme "cat")
  - après chaque sigquit (même tests que sigint)
  - exit (CTRL-D, exit seul, exit avec un argument, exit avec un argument non numérique, exit avec trop d'arguments)
- Essayer chaque builtin seul (ex: "echo"), avec un argument, avec deux arguments, avec 15 arguments, avec un argument super long...
- Suivre la correction que tu as trouvée sur Notion, tester plein de parsing avec quotes et $
- Tester le bon fonctionnement avec env -i
- Tester plusieurs commandes vides (entrée sans rien écrit, "" '', "'''"""'"...)
