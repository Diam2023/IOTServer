import { Injectable, inject } from '@angular/core';
import { ActionAll } from '../model/actionAll';
import { AppCache } from '../utils/AppCache';
import { Action } from '../model/action';

@Injectable({
  providedIn: 'root'
})

export class ActionService {

  getAllApiUrl = "http://localhost:8089/api/action/all";
  newActionApiUrl = "http://localhost:8089/api/action/new";
  deleteActionApiUrl = "http://localhost:8089/api/action/delete";



  actionAll: ActionAll | undefined;

  private async getAllAction(): Promise<ActionAll> {
    const data = await fetch(this.getAllApiUrl,
      {
        method: "GET",
        headers: {
          "Authorization": this.appCache.getToken().toString(),
        },
      });
    return await data.json() ?? [];
  };

  constructor(private appCache: AppCache) {
  }

  public async getActions(sn: String): Promise<Array<Action>> {

    try {
      this.actionAll = await this.getAllAction();
    } catch (error) {
      console.error(error);
    }


    let resultActions: Array<Action> = new Array<Action>;
    if (this.actionAll == undefined) {
      console.log("Fetch Action null!");
      return resultActions;
    }

    let targetId: Number = -1;
    for (let index = 0; index < this.actionAll.devices.length; index++) {
      const device = this.actionAll.devices[index];
      // console.log("compare: " + device.device_sn + " = " + sn);
      if (device.device_sn == sn) {
        targetId = device.device_id;
        break;
      }
    }

    if (targetId == -1) {
      // console.log("None TargetId Action");
      return resultActions;
    }

    for (let index = 0; index < this.actionAll.actions.length; index++) {
      const action = this.actionAll.actions[index];
      // console.log("loop action push");
      if (action.target_device_id == targetId) {
        resultActions.push(action);
      }
    }

    return resultActions;
  }
}
