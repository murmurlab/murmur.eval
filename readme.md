
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