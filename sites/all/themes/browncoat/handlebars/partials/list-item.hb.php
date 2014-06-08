{{#each this.below}}
<li class="{{#if @first}}first {{/if}}item{{#if @last}} last{{/if}}">
  <a data-nid="{{this.nid}}" href="{{this.path}}">{{this.title}}</a>
  {{#if this.below}}
    <ul>{{> list-item}}</ul>
  {{/if}}
</li>
{{/each}}