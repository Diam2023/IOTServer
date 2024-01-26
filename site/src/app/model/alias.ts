import { Injectable } from "@angular/core";


export interface Alias {
    alias_map_id: number;
    target_user_id: number;
    target_device_id: number;
    alias_name: string;
}
