import { Injectable } from "@angular/core";

@Injectable({
    providedIn: 'root'
})

export class DataStorge {

    public localStorage: any;

    constructor() {
        if (!localStorage) {
            throw new Error('Current browser does not support Local Storage');
        }
        this.localStorage = localStorage;
    }

    public set(key: string, value: string): void {
        this.localStorage[key] = value;
    }

    public get(key: string): string {
        return this.localStorage[key] || false;
    }

    public setArr(key: string, value: Array<any>): void {
        this.localStorage[key] = value;
    }

    public setObject(key: string, value: any): void {
        this.localStorage[key] = JSON.stringify(value);
    }

    public getObject(key: string): any {
        return JSON.parse(this.localStorage[key] || '{}');
    }

    public remove(key: string): any {
        this.localStorage.removeItem(key);
    }
    public removeAll(): any {

        this.localStorage.clear();
    }
}
