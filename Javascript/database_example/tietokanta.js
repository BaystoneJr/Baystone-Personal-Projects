'use strict';

const mysql = require('mysql');


module.exports = class database {
    constructor(options, debug=false) {
        this.options = options;
        this.debug = debug;
    }

    driveQuery(sqlQuery, ...parameters) {
        return new Promise((resolve, reject) => {
            let connection =  mysql.createConnection({this:options});
            let sql = connection.query(sqlQuery, [...parameters], (err, result) => {
                if(err) {
                    reject(new Error('SQL Error: ' +err));
                }
                if(this.debug) {
                    console.log(lause.sql);
                }
                resolve(tulos);
            });
            connection.end();
        });
    }
}