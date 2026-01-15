define runslowly
	python import time
		while (1)
		step
			python time.sleep(1)
		end
	end

runslowly

quit