import fs from "fs";
import * as coords from "./data/coords.json" assert { type: "json" };
import * as metro from "./data/stations.json" assert { type: "json" };

const coordsDefault = coords.default[0]; // line with stations and it's coordinats
const stations = metro.default[0].stations; // list of all stations itself with lined
const lines = metro.default[0].lines; // list of lines with all stations and transfer stations 
const links = metro.default[0].links; // all links belween all stations with time + time for transfer !!!!!
const transfers = metro.default[0].transfers;
const labels = metro.default[0].labels;

console.log(stations)

for(let i = 0; i < 195; i++) {
    if (stations[i].labelId != i) {
        console.log(stations[i].name)
        console.log(stations[i].labelId)
    }
}

/*
fs.writeFile('file.json', JSON.stringify(weightTime), (error) => {
    if (error) throw error;
    console.log('Данные успешно записаны в файл');
});
*/
