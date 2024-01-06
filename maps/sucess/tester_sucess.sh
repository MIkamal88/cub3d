
#!/bin/bash
for filename in $(pwd)/*.cub; do
    echo $filename
	./../../cub3D $filename
done