import { Injectable } from "@angular/core";
import { Device } from "./device";
import { Alias } from "./alias";
import { Action } from "./action";


export interface ActionAll {
    devices: Device[];
    aliases: Alias[];
    actions: Action[];
}
