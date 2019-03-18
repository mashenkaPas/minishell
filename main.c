
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include  "../libft/libft.h"

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define LSH_RL_BUFSIZE 1024
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **a);
int lsh_setenv(char **args);
int lsh_unsetenv(char **name);
int env(char **args);

typedef struct        s_node
{
    char            *type;
    char            *data;  
    struct s_node    *next;
}                    t_node;

typedef struct s_env
{
  char              *key;
  char              *value;
  struct s_env      *next;
}                   t_env;

t_env *ptm = NULL;

void  add_to_env(char *key, char *value)
{
    t_env        *begining;
    t_env       *node;
    if (!ptm)
    {
        ptm = (t_env *)malloc(sizeof(t_env));
        ptm->key = ft_strdup(key);
        if (value)
          ptm->value = ft_strdup(value);
        else
          ptm->value = ft_strdup("");
        ptm->next = NULL;
    }
    node = (t_env *)malloc(sizeof(t_env));
    begining = ptm;
    node->next = NULL;
    node->key = ft_strdup(key);
    if (value)
      node->value = ft_strdup(value);
    else
      node->value = ft_strdup("");   
    while (begining->next)
      begining = begining->next;
    begining->next = node;
    
}

void  print_env() {
    t_env *current_node = ptm;
       while ( current_node != NULL) {
        printf("%s=", current_node->key);
        if (current_node->value)
          printf("%s", current_node->value);
        printf("\n");
        current_node = current_node->next;
    }
}

void    create_env()
{
  extern char **environ;
  int       i;
  char      **tmp;

  i = 0;
  while (environ[i])
  {
    tmp = ft_strsplit(environ[i], '=');
     add_to_env( tmp[0], tmp[1]);
    ++i;
  }
  free(*tmp);

  // free(ptm);
  // return (ptm);
}


char  *search_by_key(char *key)
{
  t_env *current_node = ptm;
  while((current_node != NULL) && (ft_strcmp(current_node->key,key) != 0))
     current_node = current_node->next;
  if (current_node == NULL)
    return "EMPTY";
  else 
    return(current_node->value);  
}

void replace_value(char *key, char *new_value)
{
  t_env *current_node = ptm;

  while((current_node != NULL) && (ft_strcmp(current_node->key,key) != 0))
     current_node = current_node->next;
  if (!current_node)
    return ;
  if (new_value)
    current_node->value = new_value;
  else
    current_node->value = ft_strdup("");
  
}

void  true_setenv(char *key, char *value)
{
  if (ft_strcmp("EMPTY", search_by_key(key)) == 0)
  {
      add_to_env(key, value);
      
  }
  else{
      replace_value(key,value);
  }
}

void		free_node(t_env *list)
{
	free(list->key);
  free(list->value);
	free(list);
}

void     delete_list_env( char *key)
{
	t_env		*head;
	t_env		*tmp;

	head = ptm;
	if (ft_strcmp(ptm->key, key) == 0)
	{
		tmp = ptm;
    ptm = ptm->next;
		free_node(tmp);
    return ;
	}
	while (head && head->next && ft_strcmp(head->next->key, key))
		head = head->next;
	if (head && head->next && !ft_strcmp(head->next->key, key))
	{
		tmp = head->next;
		head->next = head->next->next;
		free_node(tmp);
	}
	else if (head && !ft_strcmp(head->key, key))
	{
		tmp = head;
		head->next = NULL;
		free_node(tmp);
	}
}

char	*ft_update(char *str, char *update)
{
	char *tmp;

	tmp = update;
	if (str != NULL)
		free(str);
	str = update;
	return (str);
}

int		ft_list_size_env (t_env *root)
{
	int		i;
	t_env	*entity;

	i = 1;
	if (!root)
		return (0);
	if (root)
	{
		entity = root;
		while (entity)
			(entity = entity->next) && i++;
	}
	return (i);
}

char	**list_to_arr_env(t_env *list)
{
	int		i;
	int		length;
	char	**new;
	t_env	*tmp;

	tmp = list;
	length = ft_list_size_env(list);
	new = (char **)malloc(sizeof(char *) * (length + 1));
	i = 0;
	while (i < length)
	{
    new[i] = ft_strjoin (list->key, "=");
    new[i] = ft_update(new[i], ft_strjoin(new[i], list->value));
		list = list->next;
		++i;
	}
	new[i] = NULL;
	//free(tmp);// ft_list_clean(&tmp);
	return (new);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

void print(t_node *list) {
    t_node *current_node = list;
       while ( current_node != NULL) {
        printf("%s \n", current_node->data);
        current_node = current_node->next;
    }
}

int		ft_list_size(t_node *root)
{
	int		i;
	t_node	*entity;

	i = 1;
	if (!root)
		return (0);
	if (root)
	{
		entity = root;
		while (entity)
			(entity = entity->next) && i++;
	}
	return (i);
}

char	**list_to_arr(t_node *list)
{
	int		i;
	int		length;
	char	**new;
	t_node	*tmp;

	tmp = list;
	length = ft_list_size(list);
	new = (char **)malloc(sizeof(char *) * (length + 1));
	i = 0;
	while (i < length)
	{
		new[i] = ft_strdup(list->data);
		list = list->next;
		++i;
	}
	new[i] = NULL;
	//free(tmp);// ft_list_clean(&tmp);
	return (new);
}


char *valid_tilda(char *type, char *data)
{
  char *newdata;
  char *tmp;

  if(*data && ft_strcmp(type, "space") == 0 && data[0] == '~')
  {
    data++;
    tmp = ft_strdup(search_by_key("HOME"));
    if(*data)
      newdata = ft_strjoin(tmp, data);
    else 
      newdata =ft_strjoin(tmp,"/");
    free(tmp);
     return newdata;
  }

  return data;
}
  

char *manage_dollar(char *type,char *data)
{
  char *newdata;
  char *tmp;
  int i;
  i = 0;
  if(*data &&ft_strcmp(type, "space") == 0 && data[0] == '$')
  {
    data++;
    if (*data)
    {
      if (ft_strcmp(search_by_key(data), "EMPTY"))
      {
        newdata = ft_strdup(search_by_key(data));
        return newdata;
      }else
        return "there is no env like this ";
    }else
      return "$";
  }
   return data;
}

t_node *add_to_list(t_node *list, char *type,char *data)
{
    t_node        *begining;
    t_node        *node;
    char          *newdata;
    newdata =  manage_dollar(type, valid_tilda(type, data));
    if (!list)
    {
        list = (t_node *)malloc(sizeof(t_node));
        list->type = ft_strdup(type);
        list->data = ft_strdup(newdata);
        list->next = NULL;
      return (list);
    }
    node = (t_node *)malloc(sizeof(t_list));
    begining = list;
    node->next = NULL;
    node->type = ft_strdup(type);
    node->data = ft_strdup(newdata);
    while (begining->next)
        begining = begining->next;
    begining->next = node;
    return (list);
}

int  ft_checker (char *str)
{
  int i = 0;
  while(str[i])
  {
    if (str[i] == 34 || str[i] == 39)
      return(i);
    i++;
  }
  return (i);
}

char **split2(char *str)
{
  t_node *list;
  list = NULL;
  char **args;
  int j, i, k;
  j = 0;
  i = 0;
  k = 0;
  while(*str){
    if (*str  && *str != 34 && *str != 39)
    {   
        i = 0;
        j = ft_checker(str);
        char *strspac = ft_strnew(j);
        strspac = ft_strncpy(strspac, str, j);
        while (strspac[k])
        {
          if(ft_ispace(strspac[k]))
            strspac[k] = ' ';
          k++;
        }
        args = ft_strsplit(strspac, ' ');
        while(args[i])
        {
          list = add_to_list(list, "space", args[i]);
          i++;
        }
        free(strspac);
        free(args);
       str = str + j;
    }
    if(*str == 34 || *str == 39)
    {
        j = 1;
        while(str[j] && (str[j] != *str))
          j++;
        if (!str[j]){
          printf("error");
           exit(1);
        }
        if(*str == str[j])
        {
          char *strqer = ft_strnew(j - 1);
          strqer = ft_strncpy(strqer,str + 1, j - 1);
          list = add_to_list(list, "special", strqer);
          free(strqer);
          str = str + j + 1;
        }
    }
  }  
  char **new = list_to_arr(list);
 // print(list);
  free(list);
  return new;
}
////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
char *builtin_str[] = {
  "cd","exit","help","env","setenv","unsetenv"
  // "env","setenv","unsetenv",
};


int (*builtin_func[]) (char **) = {
  &lsh_cd, &lsh_exit, &lsh_help, &env, &lsh_setenv ,&lsh_unsetenv,
  // &env,&setenv,&unsetenv,
};

int env(char **args){
  print_env();
  return 1;
}

int lsh_unsetenv(char **key)
{
    if (ft_strcmp(search_by_key(key[1]),"EMPTY") != 0){
        delete_list_env(key[1]);
    }
    return 1;
}

int lsh_setenv(char **args)
{
  char **tmp;

  if(ft_strchr(args[1], '=') == NULL)
  {
    if (args[2])
      true_setenv(args[1], args[2]);
    else
      true_setenv(args[1], NULL);      
  }
  else
  {
    tmp = ft_strsplit(args[1], '=');
    true_setenv(tmp[0], tmp[1]);
  }
  return 1;
}

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}


int lsh_cd(char **args)
{
  char c_pwd[64];
  char n_pwd[64];

  if (args[1] == NULL) 
  {
      getwd(c_pwd);
      replace_value("OLDPWD", ft_strdup(c_pwd));
      if (chdir(search_by_key("HOME")) != 0) {
        perror("lsh");
    }
  } 
  else {
    getwd(c_pwd);

    if (!ft_strcmp("-", args[1]))
    {
        if (chdir(search_by_key("OLDPWD")) != 0) 
          perror("lsh");
        printf("%s\n", getwd(n_pwd));
    }
    else
      if (chdir(args[1]) != 0) 
        perror("lsh");
    replace_value("OLDPWD", ft_strdup(c_pwd));
    getwd(n_pwd);
    replace_value("PWD", ft_strdup(n_pwd));
  }

  return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }
  printf("Use the man command for information on other programs.\n");
  return 1;
}

int lsh_exit(char **args)
{
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

void		print_command(char *path, char **argv)
{
	pid_t	pid;
	char	**execve_bitch;

	execve_bitch = list_to_arr_env(ptm);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, execve_bitch) == -1)
			printf("minishell: command not found: %s\n", path);
		exit(-1);
	}
	else if (pid == -1)
	{
		printf("Unable to fork process\n");
		exit(-1);
	}
	if (pid >= 1)
		wait(&pid);
	// ft_clean_arr(&execve_bitch);
}

int			check_if_path_exists(char **p, char *path, char **args)
{
	int		i;

	i = -1;
	while (p[++i])
	{
		ft_strclr(path);
		path = ft_strcat(path, p[i]);
		(args[0][0] == '/') ? 0 : ft_strcat(path, "/");
		path = ft_strcat(path, args[0]);
		if (access(path, F_OK) != -1)
		{
			print_command(path, args);
			i = -100;
			break ;
		}
	}
	// ft_clean_arr(&p);
	ft_strdel(&path);
	if (i == -100)
		return (1);
	return (-1);
}

int			find_command(char **args)
{
	char	**p;
	char	*path;

	if (!ft_strcmp("EMPTY", search_by_key("PATH")))
		return (-1);
	p = ft_strsplit(search_by_key("PATH"), ':');
	path = ft_strnew(4000);
	if (check_if_path_exists(p, path, args) == 1)
		return (0);
	return (-1);
}

void		find_command_in_dirs(char **d_comm)
{
	if (access(d_comm[0], F_OK) != -1)
		print_command(d_comm[0], d_comm);
	else if (find_command(d_comm) == -1)
		printf(" command not found %s\n", d_comm[0]);
}

// int lsh_launch(char **args)
// {
//   pid_t pid, wpid;
//   int status;
//   char **env;
//   pid = fork();
//   env = list_to_arr_env(ptm);
//   // free(&ptm);
//   if (pid == 0) {
//     // if (execvp(args[0], args) == -1) {
//     //   perror("lsh");
//     // }
//      if (execve(search_by_key("PATH"), args, env) == -1) {
//       perror("lsh");
//     }
//     exit(EXIT_FAILURE);
//   } else if (pid < 0) {
//     perror("lsh");
//   } else {
//     do {
//       wpid = waitpid(pid, &status, WUNTRACED);
//     } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//   }

//   return 1;
// }

int lsh_execute(char **args)
{ 
  int i;
  if (args[0] == NULL) {
    return 1;
  }
  for (i = 0; i < lsh_num_builtins(); i++) {
    if (ft_strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  find_command_in_dirs(args);
  return 1;
}


void lsh_loop(void)
{
  char *line;
  char **args;
  int status;


  do {
    printf("> ");
    //get_next_line(0, &line);
    line = lsh_read_line();
    args = split2(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main() {
  // printf("%s",getenv("PATH"));
  create_env();
  lsh_loop();
  // char *str = "                 cd ~/Masha ";
  // char **args = split2(str);

  free(ptm);
  return 0;
}






