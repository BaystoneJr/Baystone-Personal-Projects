'use strict';

const path = require('path');
const express = require('express');
const app = express();
const http = require('http').Server(app);

const port = 3000;
const host = 'localhost';

app.use('/js', express.static(path.join(__dirname, 'js')));
app.use('/styles', express.static(path.join(__dirname, 'styles')));
app.use('/pictures', express.static(path.join(__dirname, 'pictures')));

app.get('/', (req, res)=> {
    res.sendFile(path.join(__dirname, 'index.html'));
});

http.listen(port, host, ()=> {
    console.log(`${host} listenes on port ${port}`);
});