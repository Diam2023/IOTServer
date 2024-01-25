import { Injectable } from '@angular/core';
import { Observable, Subject, map } from 'rxjs';
import { WebsocketService } from './websocket.service';
import { AppCache } from '../utils/AppCache';


export interface Message {
    topic: string,
    json: string
}

@Injectable({
    providedIn: 'root'
})

export class NotifyService {
    notifyApiUrl = 'ws://localhost:8089/api/device/notify';

    public messages: Subject<Message>;

    constructor(private wsService: WebsocketService, private appCache: AppCache) {
        this.messages = <Subject<Message>>wsService
            .connect(this.notifyApiUrl)
            .pipe(map((response: MessageEvent): Message => {
                let data = JSON.parse(response.data);
                return {
                    topic: data.topic,
                    json: data.json
                }
            }));
    }
}