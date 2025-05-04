async function main() {
    const PAYLOAD = window.workingDir + '/sample.elf';
    const ARGS = []
    const ENVVARS = {};

    return {
        mainText: "Sample",
        secondaryText: 'Sample',
        onclick: async () => {
	    return {
		path: PAYLOAD,
		args: ARGS,
		env: ENVVARS
	    };
        }
    };
}
