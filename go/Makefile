TARGETS :=
TARGETS += hello
TARGETS += io.Copy io.Copy.Pipe io.Copy.Std
TARGETS += fibonacci
TARGETS += pi
#TARGETS += ignition
TARGETS += write

all: ${TARGETS}

${TARGETS}:
	go build $(@).go

clean:
	rm -f ${TARGETS}
