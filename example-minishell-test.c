#include "testing.h"
#include "include.h"

t_list	*ll_nod(t_list *node, int index)
{
	if (index < 0)
		return (0);
	while (index-- > 0 && node->next)
		node = node->next;
	if (index > -1)
		return (0);
	return (node);
}

void	lliter(t_list *lst, void (*f)(void *, void *), void *p)
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content, p);
		lst = lst->next;
	}
}

void	list_cmds(t_main *data)
{
	for (size_t i = 0; i < (data)->cmd_ct; i++)
	{
		t_list		*arg = (data)->cmds[i].args;
		printf("> path: %s\n", (data)->cmds[i].cmd);
		for (size_t i = 0; arg; i++)
		{
			printf(">  arg[%zu]: %s\n", i, (char *)arg->content);
			arg = arg->next;
		}
		printf("> in: %i\n", data->cmds[i].in);
		printf("> out: %i\n", data->cmds[i].out);
	}
}

t_list	*ll_nod(t_list *node, int index);

void	complex_len_test_ko(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	char    *result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	printf("=============== %s ============\n", test->current_test->name);
    printf("try		[ %s ]\n", (char *)try->try);
	printf(YELLOW"your		[ %zu ]\n"RESET, (size_t)(try->result));
	printf("expected	[ %zu ]\n", (size_t)(try->expected));
	printf("^^^^^^^^=========TEST %zu=%s================\n\n\n", test->test_number, result[1]);
}

void	complex_len_test_ok(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	char    *result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	printf("=============== %s ================\n", test->current_test->name);
    printf("try         [ %s ]\n", (char *)try->try);
    printf("expected    [ %zu ]\n", (size_t)try->expected);
	printf("=================TEST %zu=%s================\n\n\n", test->test_number, result[0]);
}

int		complex_len_test(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	((t_main *)(test->my_data))->line = try->try;
	try->result = (void *)len_all(test->my_data, 0);
	if ((size_t)try->result == (size_t)try->expected)
		return (1);
	return (0);
}

void	expand_test_ko(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	char    *result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	printf("================ %s ================\n", test->current_test->name);
    printf("try		[ %s ]\n", (char *)try->try);
	if (try->err_bit & 1)
		printf(YELLOW"your		[ %s ]\n"RESET, (char *)((void **)try->result)[0]);
	printf("expected	[ %s ]\n\n", (char *)((void **)try->expected)[0]);
	if (try->err_bit & 2)
		printf(YELLOW"your		[ %zu ]\n"RESET, ((size_t *)((void **)try->result)[1])[0]);
	printf("expected	[ %zu ]\n\n", (size_t)((void **)try->expected)[1]);
	if (try->err_bit & 4)
		printf(YELLOW"your		[ %zu ]\n"RESET, ((size_t *)((void **)try->result)[1])[1]);
	printf("expected	[ %zu ]\n\n", (size_t)((void **)try->expected)[2]);
	printf("^^^^^^^^=========TEST %zu=%s================\n\n\n", test->test_number, result[1]);
}

void	expand_test_ok(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	char    *result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	printf("=============== %s ================\n", test->current_test->name);
    printf("try         	[ %s ]\n", (char *)try->try);
    printf("expected    	[ %s ]\n", (char *)((void **)try->expected)[0]);
	printf("expected	[ %zu ]\n", (size_t)((void **)try->expected)[1]);
	printf("expected	[ %zu ]\n", (size_t)((void **)try->expected)[2]);
	printf("=================TEST %zu=%s================\n\n\n", test->test_number, result[0]);
}

int     expand_test(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	try->result = malloc(sizeof(void *) * 2);
    ((t_main *)(test->my_data))->line = try->try;
    ((void **)try->result)[0] = calloc(strlen(try->try), 2);
    ((void **)try->result)[1] = expander_exp(test->my_data, ((void **)try->result)[0], 0);
	try->err_bit |= (strcmp(((void **)try->expected)[0], ((void **)try->result)[0]) && 1) << 0;
	try->err_bit |= (((size_t *)((void **)try->result)[1])[0] != \
					(size_t)((void **)try->expected)[1] && 1) << 1;
	try->err_bit |= (((size_t *)((void **)try->result)[1])[1] != \
					(size_t)((void **)try->expected)[2] && 1) << 2;
    if (try->err_bit)
        return (0);
    return (1);
}

void	join_all_test_ko(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	char    *result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	printf("=============== %s ============\n", test->current_test->name);
    printf("try		[ %s ]\n", (char *)try->try);
	printf(YELLOW"your		[ %s ]\n"RESET, (char *)try->result);
	printf("expected	[ %s ]\n", (char *)try->expected);
	printf("^^^^^^^^=========TEST %zu=%s================\n\n\n", test->test_number, result[1]);
}

void	join_all_test_ok(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	char    *result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	printf("=============== %s ================\n", test->current_test->name);
    printf("try         [ %s ]\n", (char *)try->try);
    printf("expected    [ %s ]\n", (char *)try->expected);
	printf("=================TEST %zu=%s================\n\n\n", test->test_number, result[0]);
}

int		join_all_test(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	((t_main *)(test->my_data))->line = try->try;
	try->result = join_all(test->my_data, 0).buffer;
	if (!strcmp(try->expected, try->result))
		return (1);
	return (0);
}

void	parser_test_ko(t_test *test)
{
	char const	*result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	t_try const	*try = test->current_test->trys;
	char const	**exp = try->expected;
	t_list const	*res = try->result;

	printf("=============== %s ================\n", test->current_test->name);
    printf("try         [ %s ]\n\n", (char *)try->try);
	for (size_t i = 0; ll_nod((t_list *)res, i); i++)
		printf(YELLOW"your		[ %s ]\n"RESET, (char *)ll_nod((t_list *)res, i)->content);
	printf("\n");
	for (size_t i = 0; exp[i]; i++)
		printf("expected	[ %s ]\n", exp[i]);
	printf("^^^^^^^^=========TEST %zu=%s================\n\n\n", test->test_number, result[1]);
}

void	parser_test_ok(t_test *test)
{
	char const	*result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	t_try const	*try = test->current_test->trys;
	char const	**exp = try->expected;

	printf("=============== %s ================\n", test->current_test->name);
    printf("try         [ %s ]\n\n", (char *)try->try);
	for (size_t i = 0; exp[i]; i++)
		printf("expected    [ %s ]\n", exp[i]);
	printf("=================TEST %zu=%s================\n\n\n", test->test_number, result[0]);
}

int		parser_test(t_test *test)
{
	t_try	*try;
	t_list	*res;
	char	**exp;
	// "33",
	// "33aaaa",
	// "000011",
	// "1122",
	// "22",
	// "2233",
	// "33xxxx"
	try = test->current_test->trys;
	((t_main *)(test->my_data))->line = try->try;
	// printf("%d\n", parser(test->my_data, 0).index);
	try->result = expander(test->my_data, 0).nodes;
	res = try->result;
	exp = try->expected;
	for (size_t i = 0; exp[i] ; i++)
	{
		if ((ll_nod(res, i) && 1) ^ (exp[i] && 1))
			return (0);
		if (strcmp(ll_nod(res, i)->content, exp[i]))
			return (0);
	}
	return (1);
}

void	*get_my_data(void)
{
	t_main *data = malloc(sizeof(t_main));
	ft_bzero(data->increases, INT8_MAX);
	data->increases['"'] = (char)2;
	data->increases['\''] = (char)2;
	// data->increases['$'] = (char)1;
	data->increases[0] = (char)0;
	data->vars = NULL;
	set(data, strdup("_=./program"));
	set(data, strdup("a=0000"));
	set(data, strdup("b=11 11"));
	set(data, strdup("c=22 22 22"));
	set(data, strdup("d=33 33"));
	
	data->cmd_ct = 5;
	return (data);
}

# define SIMPLEX(res)	(res & 1 << 0)
# define DUPLEX(res)	(res & 1 << 1)

void	print_tlist(t_list *head)
{
	printf(">  [\n");
	a:
	printf(">  node: %s\n", (char *)head->content);
	head = head->next;
	if (head)
		goto a;
	printf(">  ]\n");
}

void	test_main()
{
	// printf("%s: %s\n", __func__, turn.buffer);

	// test for syntax_check(): duplex and simplex must be 0 when it should be.
	// test for parser(): must give correct out.

    // create test struct
	t_test	test;
	test.my_data = get_my_data();
	printf("# %s\n", getenv("PATH"));
	// printf("> %s\n", ((t_main *)test.my_data)->line = "$ast '' >>'\"'");
	// int res;
	// printf("> %i\n", SIMPLEX(res = syntax_check(test.my_data)));
	// printf("> %i\n", DUPLEX(res));
	// exit(0);


    // join_all(test.my_data, ,)

    // ============================= EXECUTER =============================
	// ((t_main *)test.my_data)->cmds = (t_cmd []){
	// 	{
	// 		.cmd = ft_strdup("/usr/bin/ls"),
	// 		.args = (char *[]){"", "-la", "-s", "/home/mehmetap/sources/repos/projects/main/murmursh-copyxd", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// 	{
	// 		.cmd = ft_strdup("grep"),
	// 		.args = (char *[]){"", "\\-rw-r--r--", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// 	{
	// 		.cmd = ft_strdup("cut"),
	// 		.args = (char *[]){"", "-b", "57-", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// 	{
	// 		.cmd = ft_strdup("/usr/bin/cat"),
	// 		.args = (char *[]){"", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// 	{
	// 		.cmd = ft_strdup("wc"),
	// 		.args = (char *[]){"", "-l", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// };
	// set_path(test.my_data);
	// for (size_t i = 0; i < ((t_main *)test.my_data)->cmd_ct; i++)
	// {
	// 	printf("path: %s\n", ((t_main *)test.my_data)->cmds[i].cmd);
	// }
	// exe_cute_cat(test.my_data);

    // ============================= deneme =============================
	// char const * const s = "/mnt/c/Users/Administrator/sources/repos/projects/main/murmursh-copyxd/ls";
	// char const * const s2 = "/mnt/c/Users/Administrator/sources/repos/projects/main/murmursh-copyxd";
	// execve(s, (char *const []){s , s2, "-p", NULL}, NULL);
	// char *buf = malloc(300);
	// chdir("/home/mehmetap/sources/repos/projects/main/murmursh-copyxd");
	// getcwd(buf, 300);
	// printf("%s\n", buf);
	// struct stat sb;
	// perror("hata: ");
	// ERANGE
	// printf("astast %s\n", strerror(1));
	// stat("aa/ahmet", &sb);
	// access("/home/mehmetap/sources/repos/projects/main/murmursh-copyxd/Makefile", X_OK);
	// printf("%d\n", errno);
	// perror("hata: ");
	// resolve("./program");
	// printf("res: %s\n", check_cmd("ls"));
	// printf("; %s\n", );

    // ============================= STRING =============================
	t_try	*trys[] =
	{
		(t_try [])
		{
            {
                .try = &(t_fun){complex_len_test, complex_len_test_ko, complex_len_test_ok},
                .expected = "complex len test",
            },
			{
				.try = "$$",
				.expected = (void *)2,
			},
			{
				.try = "$a",
				.expected = (void *)0,
			},
			{
				.try = "$$a",
				.expected = (void *)1,
			},
			{
				.try = "$",
				.expected = (void *)1,
			},
			{
				.try = "$a$",
				.expected = (void *)0,
			},
			{
				.try = "1",
				.expected = (void *)1,
			},
			{
				.try = "",
				.expected = (void *)0,
			},
			{
				.try = "\"$$\"",
				.expected = (void *)2,
			},
			{
				.try = "\"$a\"",
				.expected = (void *)4,
			},
			{
				.try = "\"$$a\"",
				.expected = (void *)5,
			},
			{
				.try = "\"$\"",
				.expected = (void *)1,
			},
			{
				.try = "\"$a$\"",
				.expected = (void *)5,
			},
			{
				.try = "\"\"",
				.expected = (void *)0,
			},
			{
				.try = "\"1\"",
				.expected = (void *)1,
			},
			{
				.try = "a$\"a$a=$a99\"$-$'$'$''$\"\"$\"$\"$-$-$$-$$=11$$",
				.expected = (void *)30,
			},
			{
				.try = "\"a$a99-$a\"",
				.expected = (void *)6,
			},
			{
				.try = "123123'123'1\"12\"1",
				.expected = (void *)13,
			},
			{
				.try = "1$a'$a'\"\"1\"\"$a''$a $a",
				.expected = (void *)1,
			},
			{
				.try = "\"a$\"a$a=$a99\"$-$'$'$''$\"\"$\"$\"$-$-$$-$$=11$$\"",
				.expected = (void *)3,
			},
			{
				.try = NULL,
				.expected = NULL,
			}
		},

		(t_try [])
		{
            {
                .try = &(t_fun){expand_test, expand_test_ko, expand_test_ok},
                .expected = "dquote test",
            },
			{
                .try = "\"a$a=$a99\"$-$'$'$''$\"\"$\"$\"$-$-$$-$$=11$$",
                .expected = &(void *[3]){
                    "a0000=",
                    (void *)10,
                    (void *)6
                }
            },
            {
                .try = "\"ast\"",
                .expected = &(void *[3]){
                    "ast",
                    (void *)5,
                    (void *)3
                }
            },
            {
                .try = "\"\"",
                .expected = &(void *[3]){
                    "",
                    (void *)2,
                    (void *)0
                }
            },
            {
                .try = "\"$a\"",
                .expected = &(void *[3]){
                    VAR,
                    (void *)4,
                    (void *)(0 + VAR_LEN)
                }
            },
            {
                .try = "\"$a1\"",
                .expected = &(void *[3]){
                    "",
                    (void *)5,
                    (void *)0
                }
            },
            {
                .try = "\"$-\"",
                .expected = &(void *[3]){
                    "$-",
                    (void *)4,
                    (void *)2
                }
            },
            {
                .try = "\"$\"",
                .expected = &(void *[3]){
                    "$",
                    (void *)3,
                    (void *)1
                }
            },
            {
                .try = "\"$$\"",
                .expected = &(void *[3]){
                    "$$",
                    (void *)4,
                    (void *)2
                }
            },
            {
                .try = "\"1$a\"",
                .expected = &(void *[3]){
                    "1"VAR,
                    (void *)5,
                    (void *)(1 + VAR_LEN)
                }
            },
            {
                .try = "\"-$\"",
                .expected = &(void *[3]){
                    "-$",
                    (void *)4,
                    (void *)2
                }
            },
            {
                .try = "\"a$\"",
                .expected = &(void *[3]){
                    "a$",
                    (void *)4,
                    (void *)2
                }
            },
            {
                .try = "\"$$$\"",
                .expected = &(void *[3]){
                    "$$$",
                    (void *)5,
                    (void *)3
                } //len test
            },
            {
                .try = "\"$a-\"",
                .expected = &(void *[3]){
                    VAR"-",
                    (void *)5,
                    (void *)(VAR_LEN + 1)
                }
            },
            {
                .try = "\"$$a\"",
                .expected = &(void *[3]){
                    "$"VAR,
                    (void *)5,
                    (void *)(1 + VAR_LEN)
                }
            },
            {
                .try = "\"$a-$\"",
                .expected = &(void *[3]){
                    VAR"-$",
                    (void *)6,
                    (void *)(VAR_LEN + 2)
                }
            },
            {
                .try = "\"$a-$$\"",
                .expected = &(void *[3]){
                    VAR"-$$",
                    (void *)7,
                    (void *)(VAR_LEN + 3)
                }
            },
            {
                .try = "\"-$-$-$\"",
                .expected = &(void *[3]){
                    "-$-$-$",
                    (void *)8,
                    (void *)6
                }
            },
            {
                .try = "\"-$a$a99\"",
                .expected = &(void *[3]){
                    "-"VAR,
                    (void *)9,
                    (void *)(1 + VAR_LEN)
                }
            },
            {
                .try = "\"-$a$a$a\"",
                .expected = &(void *[3]){
                    "-"VAR VAR VAR,
                    (void *)9,
                    (void *)(1 + (VAR_LEN * 3))
                }
            },
            {
                .try = "\"$a-$a\"",
                .expected = &(void *[3]){
                    VAR"-"VAR,
                    (void *)7,
                    (void *)(VAR_LEN + 1 + VAR_LEN)
                }
            },
            {.try = NULL, .expected = NULL}
		},

		(t_try [])
		{
			{
				.try = &(t_fun){join_all_test, join_all_test_ko, join_all_test_ok},
				.expected = "join all test",
			},
			{
				.try = "a$\"a$a=$a99\"$-$'$'$''$\"\"$\"$\"$-3$-1$-2$=$11$30",
				.expected = "a$a0000=$-$$$$$$$-3$-1$-2$="
			},
			{
				.try = "123123'1\"12\"1130123'1\"12\"1130",
				.expected = "1231231\"12\"11301231121130"
			},
			{
				.try = "1'$a''$a'\"\"1\"\"\"$a\"''\"$a $a1\"",
				.expected = "1$a$a100000000 "
			},
			{
				.try = "a$\"a$a=$a99\"$-$'$'$''$\"\"$\"$\"$-$-$$-$$=11$$",
				.expected = "a$a0000=$-$$$$$$$-$-$$-$$=11$$"
			},
			{
				.try = "'$a'\"''$a''\"\"'$a'\"\"  '$a' $ $a \"\"  '$'  \"\"''\"'\"$a\"'\"$_\"'$_'-=$$\"$a\"$''$$$-$'a'4\"$a $a\"a'$a''a'\"v$a$av$\"$' ''$'a'\"$a\"'\"''\"31",
				.expected = "$a''0000'''0000'  '0000' $ 0000   '$'  ''\"$a\"./program$_-=$$0000$$$$-$a40000 0000a$aav0000$$ $a\"$a\"''31"
			},
			{
				.try = "'\"  $ $ $a \"''$'\"\"''\"'\"99\"'\"\"$_\"\"'$_'-=$$\"'$a'\"$''$$$-$'a'4\"'$a $'a\"a'$a''a'\"v$'a$'av$\"$' ''$'a'\"'$'a\"'\"''\"31\"",
				.expected = "\"  $ $ $a \"$'99'./program'./program'-=$$$a$''$$$-$'a'4$a $aa'0000''a'v$a$av$$' ''$'a'$a'31"
			},
			{
				.try = NULL,
				.expected = NULL,
			}
		},

        // (t_try [])
        // {
        //     {
		// 		.try = &(t_fun){all_len_test, all_len_test_ko, all_len_test_ok},
		// 		.expected = "all len test",
		// 	},
		// 	{
		// 		.try = "$d\"aaaa\"$a$b$c'xxxx'",
		// 		.expected = (void *)30,
		// 	},
        //     {
		// 		.try = NULL,
		// 		.expected = NULL,
		// 	}
        // },

        (t_try [])
        {
			// set(data, strdup("a"), strdup("0000"));
			// set(data, strdup("b"), strdup("11 11"));
			// set(data, strdup("c"), strdup("22 22 22"));
			// set(data, strdup("d"), strdup("33 33"));			
            {
				.try = &(t_fun){parser_test, parser_test_ko, parser_test_ok},
				.expected = "join all2 test",
			},
			{
				.try = "$d\"aaaa\"$a$b$c' xxxx'",
				.expected = (char *[]){
					"33",
					"33aaaa000011",
					"1122",
					"22",
					"22 xxxx",
					NULL
				}
			},
            {
				.try = NULL,
				.expected = NULL,
			}
        },

		NULL,
	};

    // initialize test
    init_test(&test, trys);

    // call each tests in test groups
    for (size_t j = 0; (size_t)trys[j]; j++)
    {
        for (size_t i = 0; (size_t)trys[j][i + 1].try; i++)
            tester(j, i, &test);
    }
	printf("fails: %i\n", ft_lstsize(test.fails));
    exit(0);
}
