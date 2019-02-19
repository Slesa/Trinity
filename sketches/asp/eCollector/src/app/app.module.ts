import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { AppRoutingModule } from './app-routing.module';
import { CollectComponent } from './collect/collect.component';
import { SearchComponent } from './search/search.component';
import { KnowledgeCollectorComponent } from './knowledge-collector/knowledge-collector.component';
import { KnowledgeTimelineComponent } from './knowledge-timeline/knowledge-timeline.component';

@NgModule({
  declarations: [
    AppComponent,
    CollectComponent,
    SearchComponent,
    KnowledgeCollectorComponent,
    KnowledgeTimelineComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
