import { DataStorge } from "./DataStorge";
import { Injectable } from "@angular/core";

@Injectable({
    providedIn: 'root'
})

export class AppCache
{
    constructor(private cacheStorage: DataStorge)
    {
        
    }

    public setToken(token: String) {
      this.cacheStorage.setObject("token", token);
    }
  
    public getToken(): String {
      return this.cacheStorage.getObject("token");
    }

    public isLoggedIn(): boolean
    {
        return (this.getToken().length != 0);
    }
}
