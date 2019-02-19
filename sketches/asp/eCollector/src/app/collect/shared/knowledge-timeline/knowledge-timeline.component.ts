import { Component, OnInit } from '@angular/core';

import { CollectService } from '../collect.service';
import { ITimelineModel } from '../../../shared/itimeline-model';
import { ITimelineItemModel } from '../../../shared/itimeline-item-model';
import { ITimelineRequestModel } from '../../../shared/itimeline-request-model';

@Component({
  selector: 'app-knowledge-timeline',
  templateUrl: './knowledge-timeline.component.html',
  styleUrls: ['./knowledge-timeline.component.css']
})
export class KnowledgeTimelineComponent implements OnInit {

  constructor(private _collectService: CollectService) { }

  timeline: ITimelineModel = {
    items: [],
    pageNumber: 0,
    pageSize: 15,
    overallLength: 0
  };

  ngOnInit() {
    this.loadTimeline(false);
    this._collectService.TimelineUpdated
      .subscribe(item => this.loadTimeline(false));
  }

  private loadTimeline(nextPage: boolean) {
    let timelineRequest: ITimelineRequestModel = {
      pageNumber: nextPage ? this.timeline.pageNumber : 0,
      pageSize: this.timeline.pageSize
    };

    this._collectService.LoadTimeline(timelineRequest);
  }
}
