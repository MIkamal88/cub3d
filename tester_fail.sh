#!/bin/bash
for filename in $(pwd)/maps/fail/*.cub; do
    echo $filename
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes ./cub3D $filename
	echo -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
done
