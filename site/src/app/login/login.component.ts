import { Component } from '@angular/core';
import { DataStorge } from '../utils/DataStorge';
import { FormsModule, NgModel } from '@angular/forms';
import { LoginResult } from '../model/loginRes';
import { AppCache } from '../utils/AppCache';
import { Router } from '@angular/router';

@Component({
  selector: 'app-login',
  standalone: true,
  imports: [FormsModule],
  template: `
  <section class="container">
  <div class="login-form">
    <h1 class="login-title">用户登录</h1>
      <input class="input-box" [(ngModel)]="key" type="text" placeholder="用户名" >
      <input class="input-box" [(ngModel)]="pwd" type="password" placeholder="密码">
      <div class="button-row">
        <button mat-raised-button (click)="login()" color="primary"  class="login-button">登录</button>
      </div>
  </div>
  </section>
  `,
  styleUrl: './login.component.css'
})

export class LoginComponent {

  key: String = '';
  pwd: String = '';


  loginApiUrl = "http://localhost:8089/api/user/login";
  registApiUrl = "http://localhost:8089/api/user/register";

  constructor(private appCache: AppCache, private route: Router) {
  }



  login() {

    // Filter
    if (this.key.length == 0 || this.pwd.length == 0) {
      alert("输入信息不正确");
      return;
    }

    let reqBody = {
      "key": this.key,
      "pwd": this.pwd
    }

    fetch(this.loginApiUrl,
      {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify(reqBody)
      })
      .then((response) => {

        console.log(response);

        if (!response.ok) {
          throw new Error(`HTTP error! Status: ${response.status}`);
        }

        if (response.status == 200) {
          return response.json();
        } else {
          throw new Error(`密码帐号错误`);
        }
      }).then((res: LoginResult) => {
        this.appCache.setToken(res.token);
        this.route.navigate(['/']);
      }).catch((e) => {
        console.error(e);
        alert(e);
      })
  }
}
