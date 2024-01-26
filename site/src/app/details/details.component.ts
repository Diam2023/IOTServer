import { Component, inject } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { FormControl, FormGroup, ReactiveFormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';
import { ActionService } from '../service/action.service';
import { Action } from '../model/action';
import { ActionItemComponent } from "../action-item/action-item.component";

@Component({
  selector: 'app-details',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule, ActionItemComponent],
  template: `
  <section>
    <section class="action-list">
      <app-action-item *ngFor="let actionItem of actionList" [actionItem]="actionItem"></app-action-item>
    </section>
    <button>添加行为</button>
    <button>删除设备</button>
  </section>
  `,
  styleUrl: './details.component.css'
})

export class DetailsComponent {

  route: ActivatedRoute = inject(ActivatedRoute);

  actionService: ActionService = inject(ActionService);

  actionList: Action[] | undefined;

  constructor(private router: Router) {
    const sn = String(this.route.snapshot.params['sn']);
    if (sn.length <= 0) {
    this.router.navigate(['/']);
    }

    this.actionService.getActions(sn).then(actions => {
      if (actions.length > 0) {
        // fill it
        this.actionList = actions;
      }
    });
  }
}