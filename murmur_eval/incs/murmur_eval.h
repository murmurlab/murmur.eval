#ifndef MURMUR_EVAL_H
# define MURMUR_EVAL_H
# if defined(__linux__)
	/* Linux. --------------------------------------------------- */
# elif defined(__APPLE__)
	/* OSX. --------------------------------------------------- */
# endif

#include <stdlib.h>

# ifndef TEST
#  define TEST 0
# endif

extern char			*__result_eval[2];
void				test_main(void);

# define MURMURTEST if(TEST){test_main();}

# define CURR_TEST(PARAM_t_test) ((t_try *)PARAM_t_test->current_test->trys)


# define EVAL_INIT(T_TEST, T_TRY) \
	init_test(&T_TEST, T_TRY);

# define EVAL_TEST(T_TEST, GROUP_NUM, TEST_NUM) tester(GROUP_NUM, TEST_NUM, &T_TEST);

# define EVAL_GROUP(T_TEST, T_TRY, GROUP_NUM) \
	printf("\n\n\n%s\n\n", T_TRY[GROUP_NUM][0].expected); \
	for (size_t i = 0; (size_t)T_TRY[GROUP_NUM][i + 1].try; i++) \
		EVAL_TEST(T_TEST, GROUP_NUM, i)

# define CASE .try
# define EXPECTED .expected

# define NEW_TEST_RUNNER(NUM) \
	t_test	murmur_eval_runner_id_##NUM; \

# define GET_TEST_RUNNER(NUM) \
	murmur_eval_runner_id_##NUM

# define NEW_TEST(NUM) \
	t_try	*murmur_eval_id_##NUM[] = \
	{ \

# define END_TEST \
		NULL, \
	}; \

# define GET_TEST(NUM) \
	murmur_eval_id_##NUM

# define EVAL_ALL(T_TEST, T_TRY) \
	for (size_t j = 0; (size_t)T_TRY[j]; j++) \
    { \
        EVAL_GROUP(T_TEST, T_TRY, j) \
    }

# define EVAL_FAILS(T_TEST) \
		printf("fails: %i\n", ft_lstsize(T_TEST.fails));

# define NEW_GROUP(name_of_test, tester_func, ko_func, ok_func) \
	(t_try []) \
	{ \
	{ \
		.try = &(t_fun){tester_func, ko_func, ok_func}, \
		.expected = name_of_test, \
	}, \

# define END_GROUP \
	{ \
		.try = NULL, \
		.expected = NULL, \
	} \
	},


# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define RESET "\x1B[0m"

struct s_tests;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_test
{
	size_t			test_number;
	size_t			test_group_num;

	struct s_tests	*current_test;
	struct s_list	*fails;
	struct s_list	*success;
	void			(*ko_msg)(struct s_test *test);
	void			(*ok_msg)(struct s_test *test);

	struct s_tests	**tests;
	void			*my_data;
}				t_test;

struct s_try;

typedef struct s_tests
{
	char			*name;
	int				(*test_fun)(struct s_test *test);

	void			(*ko_msg)(struct s_test *test);
	void			(*ok_msg)(struct s_test *test);

	struct s_try	*trys;
}				t_tests;

typedef struct s_try
{
	void	*try;
	void	*expected;
	void	*result;
	size_t	err_bit;
}				t_try;

typedef struct s_fun
{
	void	*test_fun;
	void	*ko_msg;
	void	*ok_msg;
}				t_fun;

// int	ft_lstsize(struct s_list *lst);
// struct s_list	*ft_lstnew(void *content);
// struct s_list	*ft_lstlast(struct s_list *lst);
// void	ft_lstadd_back(struct s_list **alst, struct s_list *new);

void    init_test(t_test *test, t_try *trys[]);
void	tester(int test_group_num, int test_num, t_test *test);

#endif
