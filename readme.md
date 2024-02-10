
This work © 2023 by murmurlab is licensed under CC BY-SA 4.0. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/

# murmur.test

INFO: dont touch [**testing/**](./testing/) folder!

create a custom test file like example-minishell-test.c
the test file must contain `void	test_main(void);` function

```c
// create test struct
t_test	test;

// pass optional data
test.my_data = get_my_data();
```
create test cases
```c
t_try	*trys[] =
	{
		// create test group
		(t_try [])
		{
			{
				// this is not test case, this is fake test case like test-head
				// you should put it here the test funcs 
				// .try is test and result funcs, .expected is test name
				.try = &(t_fun){complex_len_test, complex_len_test_ko, complex_len_test_ok},
				.expected = "complex len test",
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
				.try = "\"a$\"a$a=$a99\"$-$'$'$''$\"\"$\"$\"$-$-$$-$$=11$$\"",
				.expected = (void *)3,
			},
			{
				.try = NULL,
				.expected = NULL,
			}
		},

		// create another test group
		(t_try [])
		{
			{
				.try = &(t_fun){expand_test, expand_test_ko, expand_test_ok},
				.expected = "dquote test",
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

		// create another test group
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
				.try = NULL,
				.expected = NULL,
			}
		},

		// create another test group
		(t_try [])
		{
			{
				.try = &(t_fun){all_len_test, all_len_test_ko, all_len_test_ok},
				.expected = "all len test",
			},
			{
				.try = "$d\"aaaa\"$a$b$c'xxxx'",
				.expected = (void *)30,
			},
			{
				.try = NULL,
				.expected = NULL,
			}
		},

		// create another test group
		(t_try [])
		{			
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
```

example test func
```c
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
```
example simple ko print func
```c
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
```
**! ! ! example complex ko print func ! ! !**
```c
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
```
### The structure is like this
```c
// =============================================================================
typedef struct s_test
{
	size_t			test_number;
	size_t			test_group_num;

	struct s_tests	*current_test;
	t_list			*fails;
	t_list			*success;
	void			(*ko_msg)(struct s_test *test);
	void			(*ok_msg)(struct s_test *test);

	struct s_tests	**tests;
	void			*my_data;
}				t_test;
// =============================================================================
typedef struct s_tests
{
	char			*name;
	int				(*test_fun)(struct s_test *test);

	void			(*ko_msg)(struct s_test *test);
	void			(*ok_msg)(struct s_test *test);

	struct s_try	*trys;
}				t_tests;
// =============================================================================
typedef struct s_try
{
	void	*try;
	void	*expected;
	void	*result;
	size_t	err_bit;
}				t_try;
// =============================================================================
```

### test
```c
	// initialize test
	// pass test struct and test cases
	init_test(&test, trys);

	// call each tests in test groups
	for (size_t j = 0; (size_t)trys[j]; j++)
	{
		for (size_t i = 0; (size_t)trys[j][i + 1].try; i++)
			tester(j, i, &test);
	}
	printf("fails: %i\n", ft_lstsize(test.fails));
	exit(0);
```

to run:

compile with

> cxx [flags] -D TEST=1 *.c

run macro

```c
int main(void){
	// code
MURMURTEST;
	// code
}
```

\
example image:
![alt text](test.jpeg)
