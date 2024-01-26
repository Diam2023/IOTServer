import { Component } from '@angular/core';
import { HomeComponent } from './home/home.component';
import { Router, RouterLink, RouterModule } from '@angular/router';
import { AppCache } from './utils/AppCache';
import { ToastModule } from 'primeng/toast';
import { MessageService, PrimeNGConfig } from 'primeng/api';
import { NotifyService } from './service/notify.service';
import { WebsocketService } from './service/websocket.service';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [
    HomeComponent,
    RouterModule,
    RouterLink,
    ToastModule,
  ],
  providers: [
    MessageService
  ],
  template: `
  <main>
      <header class="main-nav">
    <a [routerLink]="['/']">
        <h1 class="main-title">IOTServer</h1>
    </a>
      </header>
    <p-toast></p-toast>
    <section class="content">
      <router-outlet></router-outlet>
    </section>
  </main>`,
  styleUrls: ['./app.component.css'],
})


export class AppComponent {
  title = 'homes';

  notifyService: NotifyService | undefined;

  public snedMessage(sum: string, msg: string) {
    this.messageService.add({ severity: 'info', summary: sum, detail: msg, });
  }

  constructor(private appCache: AppCache, private route: Router, private messageService: MessageService, private primengConfig: PrimeNGConfig) {
    this.primengConfig.ripple = true;

    if (this.notifyService == undefined) {
      if (this.appCache.isLoggedIn()) {
        console.log("init ws notify");
        this.notifyService = new NotifyService(new WebsocketService(this.appCache), this.appCache);
      }
    }

    if (this.notifyService != undefined) {
      this.notifyService.messages.subscribe(msg => {
        // TODO Splite device SN and display device name
        let res = JSON.parse(msg.json);
        // for (let index = 0; index < this.deviceList.length; index++) {
        //   const element = this.deviceList[index];
        //   element.device_sn == res.topic;
        // }

        if (res.status == undefined) {
          this.messageService.add({ severity: 'info', summary: msg.topic, detail: msg.json, });
        } else {
          if (res.status) {
            this.messageService.add({ severity: 'info', summary: msg.topic, detail: '开灯', });
          } else {
            this.messageService.add({ severity: 'info', summary: msg.topic, detail: '关灯', });
          }
        }
      });
    }

    if (!appCache.isLoggedIn()) {
      this.route.navigate(['/login']);
    }

    console.log("Logged In Cache:" + appCache.getToken());
  }

}
