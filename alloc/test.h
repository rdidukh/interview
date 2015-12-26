#define RED_COLOR 	"\033[0;31m"
#define GREEN_COLOR	"\033[0;32m"
#define NO_COLOR	"\033[0m"

#define ASSERT_NULL(x) \
	do {	\
		if((x) != NULL) \
		{	\
			std::cerr << RED_COLOR << "FAIL: " #x " != NULL" << NO_COLOR << std::endl;	\
			exit(1);	\
		} else { \
			std::cout << GREEN_COLOR << "OK: " #x " == NULL" << NO_COLOR << std::endl;	\
		} \
	} while(0);

#define ASSERT_NOTNULL(x) \
	do {	\
		if((x) == NULL) \
		{	\
			std::cerr << RED_COLOR << "FAIL: " #x " == NULL" << NO_COLOR << std::endl;	\
			exit(1);	\
		} else { \
			std::cout << GREEN_COLOR << "OK: " #x " != NULL" << NO_COLOR << std::endl;	\
		} \
	} while(0);


#define ASSERT_EQ(expected, real) \
	do {	\
		if((expected) != (real)) {	\
			std::cerr << RED_COLOR << "FAIL: " #real " != " #expected << NO_COLOR << std::endl; \
			std::cerr << #real ": " << std::endl;	\
			std::cerr << "Expected: " << (expected) << std::endl; \
			std::cerr << "Real: " << (real) << std::endl; \
			exit(1);	\
		} else { \
			std::cout << GREEN_COLOR << "OK: " #real " == " #expected << NO_COLOR << std::endl; \
		}	\
	} while(0);