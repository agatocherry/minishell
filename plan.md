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
- echo -nn bonjour
- echo -n -n -n bonjour
- expansion ~ (à faire ?)
- parsing ''''''''''$USER'''''''''' et """"""""$USER""""""""
- expansion s'arrête après le premier chiffre ($12 = $1 2 mais $USER12 != $USER1 2)
- exit -42 -24 (doit donner : too many arguments)
- exit +0 ou -4 (doit fonctionner)
- exit 9223372036854775808 (doit donner : numeric argument required)
- export doit faire : declare -x SHLVL="2" (pas declare -x SHLVL=2)
- export TEST fait segfault
- export --TEST=123 doit faire une erreur
- export = ou export "=""=""=" doit faire une erreur (export: ===: not a valid identifier)
- export TEST-=100 ou export TE-ST=100 doit faire une erreur (tous les caractères spéciaux)
- export export 1TEST= doit faire une erreur
- unset -TEST doit faire une erreur
- unset TES$?T ne doit pas faire d'erreur

