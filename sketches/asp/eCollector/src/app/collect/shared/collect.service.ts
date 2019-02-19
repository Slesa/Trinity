import { Injectable, EventEmitter } from '@angular/core';
//import { Headers, RequestOptions, Response } from '@angular/http';
import { HttpClient, HttpHeaders } from '@angular/common/http';
//import { AuthHttp } from 'angular2-jwt';
import { catchError, map, tap } from 'rxjs/operators';
import { Observable, of } from 'rxjs';

import { ICollectModel } from './icollect-model';
import { ITimelineModel } from '../../shared/itimeline-model';
import { ITimelineRequestModel } from '../../shared/itimeline-request-model';
import { UploadService } from './upload.service';

@Injectable({
  providedIn: 'root'
})
export class CollectService {

  public TimelineUpdated: EventEmitter<boolean> = new EventEmitter<boolean>();
  private _service: string = 'http://localhost:5000';

  constructor(
    private _http: HttpClient, 
    private _uploadService: UploadService
  ) { }

  Collect(collectModel: ICollectModel): Promise<boolean> {
    console.log(collectModel.text);

    let files: File[] = collectModel.files;

    return this._uploadService.upload(`${this._service}api/collect`, collectModel.text, files)
//        .then(result => this.ForceReloadTimeline(this))
//        .catch(this.handleError);
  }
  /*
  private ForceReloadTimeline(that: CollectService) {
    that.TimelineUpdated.next(true);
  }
  */
  LoadTimeline(page: ITimelineRequestModel): Observable<ITimelineModel[]> {
    /*let headers = new HttpHeaders({
      'ContentType': 'application/json',
      'Page-Number': page.pageNumber,
      'Page-Size': page.pageSize
    });
    let options = new RequestOptions({ headers: headers });*/
    return this._http.get<ITimelineModel[]>(`${this._service}api/timeline`/*, options*/)
      .pipe(
        tap(_ => this.log('fetched Timeline')),
        catchError(this.handleError<ITimelineModel[]>(`LoadTimeline`, []))
      );
  }

  private log(message: string) {
    console.log(message);
    //this.messageService.add(`UploadService: ${message}`);
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error:any): Observable<T> => {
      //this.log(`${operation} failed: ${error.message}`);
      return of(result as T);
    }
  }
}
