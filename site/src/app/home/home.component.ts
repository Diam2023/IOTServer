import { Component, inject } from '@angular/core';
import { HousingLocationComponent } from '../housing-location/housing-location.component';
import { CommonModule } from '@angular/common';
import { HousingLocation } from '../housinglocation';
import { HousingService } from '../housing.service';
import { AppCache } from '../utils/AppCache';
import { Router } from '@angular/router';
import { DeviceService } from '../service/device.service';
import { Device } from '../model/device';
import { DeviceItemComponent } from '../device-item/device-item.component';
import { FormsModule, NgModel } from '@angular/forms';
import { NotifyService } from '../service/notify.service';

@Component({
  selector: 'app-home',
  standalone: true,
  imports: [
    CommonModule,
    HousingLocationComponent,
    DeviceItemComponent,
    FormsModule
  ],
  template: `
  <section class="new-device">
    <div class="new-device-mask" (click)="hideNewDevice()">
    </div>
    <div class="new-device-frame">
      <h2 class="new-device-title">添加设备</h2>
      <input type="text" [(ngModel)]="newDeviceName" placeholder="NAME">
      <input type="text" [(ngModel)]="newDeviceSN" placeholder="SN">
      <input type="number" [(ngModel)]="newDeviceLevel" placeholder="NAME">
      <button mat-raised-button (click)="submitNewDevice()" color="primary"  class="login-button">添加</button>
    </div>
  </section>
  <section class="results">
    <section class="listing">
      <a (click)="showNewDevice()">
        <h2 class="listing-add-device">添加设备</h2>
      </a>
    </section>
    <app-device-item *ngFor="let deviceItem of deviceList" [deviceItem]="deviceItem"></app-device-item>
  </section>
  `,
  styleUrl: './home.component.css'
})

export class HomeComponent {

  deviceService: DeviceService = inject(DeviceService);
  deviceList: Device[] = [];


  newDeviceName: String = '';
  newDeviceSN: String = '';
  newDeviceComment: String = 'Default';
  newDeviceLevel: Number = 1;

  public showNewDevice() {
    document.querySelector(".new-device")?.setAttribute("style", "display: block");
  }

  public hideNewDevice() {
    document.querySelector(".new-device")?.setAttribute("style", "display: none");
  }

  public submitNewDevice() {
    if (this.newDeviceName.length > 0 && this.newDeviceSN.length > 0) {
      this.deviceService.newDevice(this.newDeviceSN, this.newDeviceName, this.newDeviceComment, this.newDeviceLevel).then(r => {
        if (r) {
          alert("成功")
          window.location.reload();
        } else {
          alert("失败")
        }
      });
    } else {
      alert("参数错误");
    }
  }

  constructor(private appCache: AppCache, private route: Router, private notifyService: NotifyService) {
    notifyService.messages.subscribe(msg => {
      console.log(msg);
    });

    // this.filteredLocationList = this.housingLocationList;
    // Fetch All Device
    this.deviceService.getAllDevice().then(d => {
      this.deviceList = d;
    }).catch(e => {
      console.error(e);
      alert("获取设备失败！")
    });
  }
}