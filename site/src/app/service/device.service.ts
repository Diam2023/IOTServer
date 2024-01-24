import { Injectable } from '@angular/core';
import { Device } from '../model/device';
import { AppCache } from '../utils/AppCache';

@Injectable({
  providedIn: 'root'
})

export class DeviceService {
  // deviceList: Device[] = [];

  getAllApiUrl = "http://localhost:8089/api/device/all";
  newDeviceApiUrl = "http://localhost:8089/api/device/new";

  constructor(private appCache: AppCache) { }

  public async getAllDevice(): Promise<Device[]> {
    const data = await fetch(this.getAllApiUrl,
      {
        method: "GET",
        headers: {
          "Authorization": this.appCache.getToken().toString(),
        },
      });
    return await data.json() ?? [];
  };


  public newDevice(sn: String, name: String, comment: String, level: Number): Promise<boolean> {


    let device = {
      "target_permission_level": level,
      "device_comment": comment,
      "device_name": name,
      "device_sn": sn
    };

    let res = fetch(this.newDeviceApiUrl,
      {
        method: "PUT",
        headers: {
          "Content-Type": "application/json",
          "Authorization": this.appCache.getToken().toString(),
        },
        body: JSON.stringify(device)
      }).then(response => {

        console.log(response);

        if (!response.ok) {
          throw new Error(`HTTP error! Status: ${response.status}`);
        }

        if (response.status == 200) {
          return true;
        } else {
          throw new Error(`密码帐号错误`);
        }
      }).catch(e => {
        console.log(e);
        return false;
      });


    return res;
  }
}
