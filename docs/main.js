fetch('./lib.json')
    .then(x => x.json())
    .then(lib => {
        console.log(lib);
    });
