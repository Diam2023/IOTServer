import { Injectable } from '@angular/core';
import { Subject, Observer, Observable } from 'rxjs'; import { AppCache } from '../utils/AppCache';


@Injectable({
    providedIn: 'root'
})

export class WebsocketService {
    constructor(private appCache: AppCache) { }

    private subject: Subject<MessageEvent> | undefined;

    public connect(url: string): Subject<MessageEvent> {
        if (!this.subject) {
            this.subject = this.create(url);
            console.log("Successfully connected: " + url);
        }
        return this.subject;
    }

    private create(url: string): Subject<MessageEvent> {
        let ws = new WebSocket(url);
        // TODO Auth
        ws.addEventListener('open', (event) => {
            ws.send(this.appCache.getToken().toString());
        });

        let observable = new Observable(
            (obs: Observer<MessageEvent>) => {
                ws.onmessage = obs.next.bind(obs);
                ws.onerror = obs.error.bind(obs);
                ws.onclose = obs.complete.bind(obs);
                return ws.close.bind(ws);
            })
        let observer = {
            next: (data: Object) => {
                if (ws.readyState === WebSocket.OPEN) {
                    ws.send(JSON.stringify(data));
                }
            }
        }
        return Subject.create(observer, observable);
    }

}