<section class="main__body">
  {{{body}}}
  {{#each custom_fields}}
    <p><strong>{{@key}}:</strong> {{this}}</p>
    {{else}}
    <p>no custom fields</p>
  {{/each}}
</section>