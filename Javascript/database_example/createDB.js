'use strict';

const Tietokanta = require('./tietokanta');

let file = './creationstatement.json';

if(process.argv.length>2) {
    file=`./${process.argv[2]}`;
}

try {
    createDatabase(require(file));
}
catch(err) {
    console.log(`Error: ${err.message}`);
}

async function createDatabase(createQueries) {
    const option = {
        host: createQueries.host,
        port: createQueries.mysqlport,
        user: createQueries.admin,
        password: createQueries.adminpassword,

    };
    let dropSql = `DROP DATABASE IF EXISTS ${createQueries.database}`;
    let createSql = `CREATE DATABASE ${createQueries.database}`;
    let dropUserSql = `DROP USER IF EXISTS ${createQueries.user} @ ${createQueries.host}`;
    let createUserSql = `CREATE USER IF NOT EXISTS ${createQueries.user} @ ${createQueries.host} IDENTIFIED BY ${createQueries.password}`;
    let privilegesSql = `GRANT ALL PRIVILEGES ON ${createQueries.database} * TO ${createQueries.user} @ ${createQueries.host}`;

    let DataBase = new DataBase(options, createQueries.debug);

    try {
        await DataBase.driveQuery(dropSql);
        await DataBase.driveQuery(createSql);
        if(createQueries.dropUser) {
            await DataBase.driveQuery(dropUserSql);
        }
        await DataBase.driveQuery(createUserSql)
        await DataBase.driveQuery(privilegesSql);
        
       for (let table of createQueries.tables) {
            let createTableSql = `CREATE TABLE ${table.name}(\n${table.rows.join(',\n')})`;
            let addSql = `INSERT INTO ${table.name} VALUES (?)`;
            await DataBase.driveQuery(createTableSql);
            let inserts = [];
            for(let data of table.data) {
                inserts.push(DataBase.driveQuery(addSql, data));
            }
            await Promise.all(inserts);
        }
    }
    catch(err) {
        console.log(err.message);
    }
}