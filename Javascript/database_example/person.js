'use strict';

module.exports = class Person {
    constructor(personID, firstname, lastname, section ='', paycheck=0){
    this.personID = personID;
    this.firstname = firstname;
    this.lastname = lastname;
    this.section = section,
    this.paycheck = paycheck
    }
    allInfo() {
        return [
            this.personID, this.firstname, this.lastname,
            this.section, this.paycheck
        ];
    }
    toString() {
        return `ID=${this.personID}: ${this.firstname} ${this.lastname}, 
        Section: ${this.section}, paycheck: ${this.paycheck}`;
    }
}