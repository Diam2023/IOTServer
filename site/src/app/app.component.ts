import { Component } from '@angular/core';
import { HomeComponent } from './home/home.component';
import { Router, RouterLink, RouterModule } from '@angular/router';
import { AppCache } from './utils/AppCache';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [
    HomeComponent,
    RouterModule,
    RouterLink
  ],
  template: `
  <main>
      <header class="main-nav">
    <a [routerLink]="['/']">
        <h1 class="main-title">IOTServer</h1>
    </a>
      </header>
    <section class="content">
      <router-outlet></router-outlet>
    </section>
  </main>`,
  styleUrls: ['./app.component.css'],
})


export class AppComponent {
  title = 'homes';
  constructor(private appCache: AppCache, private route: Router) {

    if (!appCache.isLoggedIn())
    {
      this.route.navigate(['/login']);
    }

    console.log("Logged In Cache:" + appCache.getToken());
  }

}
