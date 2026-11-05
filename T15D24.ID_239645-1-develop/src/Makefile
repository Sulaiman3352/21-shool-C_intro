FLAGS=-Wall -Werror -Wextra

all: build_db

build_db: levels.c modules.c modules_db.c shared.c status_events.c
	gcc $(FLAGS) levels.c modules.c modules_db.c shared.c status_events.c -o ../build/database -lm


clean:
	rm -rf *.o ../build/database

rebuild: clean all

.PHONY: clean all rebuild
